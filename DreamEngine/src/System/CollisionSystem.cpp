#include <System/CollisionSystem.hpp>
#include <cmath>

namespace DREAM
{



/*
Converts a world-space angular velocity (an axis + speed, in rad/s) into the
three Euler rates our rotation field actually wants, for the Rz*Ry*Rx order
used by PhysicsSystem::GetModelMatrixfromComponent.

Needed because collision produces a world axis, but rotation.x/.y/.z are
applied in sequence - so rotation.x's real-world axis depends on where y and z
currently sit. This undoes that.

    phi_dot   = ( wx*cos(psi) + wy*sin(psi) ) / cos(theta)
    theta_dot =  -wx*sin(psi) + wy*cos(psi)
    psi_dot   =   wz + phi_dot*sin(theta)

Breaks down when theta (pitch) hits +-90 deg: cos(theta) goes to zero and
rotation.x / rotation.z stop being distinguishable. That's gimbal lock, and it's
the Euler representation running out of road rather than a bug here. Clamped
below so it degrades instead of producing NaN. Quaternions remove it entirely.
*/
static Vec3<float> OmegaToEulerRates(const Vec3<float>& _omega, const Vec4<float>& _rotationDegrees)
{
	const float DEG2RAD = 0.01745329f;
	const float RAD2DEG = 57.29578f;

	float theta = _rotationDegrees.y * DEG2RAD;   // pitch
	float psi   = _rotationDegrees.z * DEG2RAD;   // yaw

	float ct = cosf(theta), st = sinf(theta);
	float cp = cosf(psi),   sp = sinf(psi);

	if (fabsf(ct) < 0.001f) ct = (ct < 0.0f ? -0.001f : 0.001f);   // gimbal guard

	float phi_dot   = ( _omega.x * cp + _omega.y * sp) / ct;
	float theta_dot = (-_omega.x * sp + _omega.y * cp);
	float psi_dot   =   _omega.z + phi_dot * st;

	return Vec3<float>(phi_dot * RAD2DEG, theta_dot * RAD2DEG, psi_dot * RAD2DEG);
}


/*
The other direction: takes the three Euler rates we have stored and works out
what world-space angular velocity they currently represent. Needed so a bounce
ADDS to the cube's existing spin instead of throwing it away.

    wx = phi_dot*cos(psi)*cos(theta) - theta_dot*sin(psi)
    wy = phi_dot*sin(psi)*cos(theta) + theta_dot*cos(psi)
    wz = -phi_dot*sin(theta) + psi_dot
*/
static Vec3<float> EulerRatesToOmega(const Vec4<float>& _ratesDegrees, const Vec4<float>& _rotationDegrees)
{
	const float DEG2RAD = 0.01745329f;

	float theta = _rotationDegrees.y * DEG2RAD;
	float psi   = _rotationDegrees.z * DEG2RAD;

	float ct = cosf(theta), st = sinf(theta);
	float cp = cosf(psi),   sp = sinf(psi);

	float phi_dot   = _ratesDegrees.x * DEG2RAD;
	float theta_dot = _ratesDegrees.y * DEG2RAD;
	float psi_dot   = _ratesDegrees.z * DEG2RAD;

	return Vec3<float>( phi_dot * cp * ct - theta_dot * sp,
	                    phi_dot * sp * ct + theta_dot * cp,
	                   -phi_dot * st     + psi_dot );
}


void CollisionSystem::update()
{
	// Ground plane. Hardcoded for now - will come from a PLANE ColliderComponent later.
	const Vec3<float> plane_normal(0.0f, 1.0f, 0.0f);
	const float plane_offset = -1.0f;      // floor sits at y = -1

	const float restitution = 0.5f;        // 0 = dead thud, 1 = perfect bounce
	const float rest_cutoff = 1.0f;        // below this speed, stop bouncing

	for (auto *entity : entities)
	{
		PhysicsComponent *physics_component  = entity->getComponent<PhysicsComponent>();
		ColliderComponent       *collidor_component = entity->getComponent<ColliderComponent>();

		if (physics_component == nullptr || collidor_component == nullptr) continue;
		if (collidor_component->type != ColliderType::BOX)                 continue;

		Mat4<float> model_matrix = PhysicsSystem::GetModelMatrixfromComponent(physics_component);
		Vec3<float> he = collidor_component->half_extents;

		// ---- find every corner that has gone through the floor ----
		Vec3<float> contact_sum(0.0f, 0.0f, 0.0f);
		int   contact_count = 0;
		float deepest = 0.0f;

		for (int i = 0; i < 8; ++i)
		{
			float sx = (i & 1) ? 1.0f : -1.0f;
			float sy = (i & 2) ? 1.0f : -1.0f;
			float sz = (i & 4) ? 1.0f : -1.0f;

			Vec4<float> cw = model_matrix * Vec4<float>(sx*he.x, sy*he.y, sz*he.z, 1.0f);
			Vec3<float> c3(cw.x, cw.y, cw.z);

			float d = Vec3<float>::dot(c3, plane_normal) - plane_offset;

			if (d < 0.0f)
			{
				contact_sum = contact_sum + c3;
				contact_count++;
				if (-d > deepest) deepest = -d;
			}
		}

		if (contact_count == 0) continue;

		// average of the penetrating corners = where we treat the hit as landing
		Vec3<float> contact_point = contact_sum * (1.0f / (float)contact_count);

		// ---- 1. push out of the floor. ONCE, by the deepest amount ----
		// (applying it per-contact would shove a flat-landing cube out 4x)
		Vec4<float> n4(plane_normal.x, plane_normal.y, plane_normal.z, 0.0f);  // w=0: a direction
		physics_component->position = physics_component->position + n4 * deepest;

		// ---- 2. impulse, including the angular part ----
		Vec3<float> com(physics_component->position.x,
		                physics_component->position.y,
		                physics_component->position.z);

		Vec3<float> r = contact_point - com;        // lever arm: centre -> contact

		Vec3<float> v(physics_component->velocity.x,
		              physics_component->velocity.y,
		              physics_component->velocity.z);

		// current angular velocity, recovered from the Euler rates we stored
		Vec3<float> w = EulerRatesToOmega(physics_component->rotation_velocity,
		                                  physics_component->rotation);

		// velocity AT the contact point, not at the centre of mass
		Vec3<float> vp = v + Vec3<float>::Cross(w, r);
		float vn = Vec3<float>::dot(vp, plane_normal);

		if (vn < 0.0f)   // only react if actually moving INTO the floor
		{
			float e = (fabsf(vn) < rest_cutoff) ? 0.0f : restitution;

			Vec3<float> r_cross_n = Vec3<float>::Cross(r, plane_normal);

			// how much the contact point's velocity changes per unit impulse:
			// linear term + rotational term. An off-centre hit has a bigger
			// rotational term, so less of the impulse becomes bounce and more
			// becomes spin. That's what makes a corner strike topple instead of leap.
			float denom = (1.0f / physics_component->mass)
			            + Vec3<float>::dot(r_cross_n, r_cross_n) / physics_component->inertia;

			float j = -(1.0f + e) * vn / denom;

			Vec3<float> impulse = plane_normal * j;

			// linear
			Vec3<float> dv = impulse * (1.0f / physics_component->mass);
			physics_component->velocity = physics_component->velocity + Vec4<float>(dv.x, dv.y, dv.z, 0.0f);

			// angular - this is the bit that makes it tip
			Vec3<float> dw = Vec3<float>::Cross(r, impulse) * (1.0f / physics_component->inertia);
			Vec3<float> new_omega = w + dw;

			// convert the world-space axis into Euler rates before storing
			Vec3<float> rates = OmegaToEulerRates(new_omega, physics_component->rotation);
			physics_component->rotation_velocity = Vec4<float>(rates.x, rates.y, rates.z, 0.0f);
		}
	}
}

void CollisionSystem::onEntityAddition(Entity* _entity)
{
	std::cout<<"Entity added to collision system"<<std::endl;
}

}
