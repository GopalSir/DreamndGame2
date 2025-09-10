#include"./System/PhysicsSystem.h"

namespace DREAM{
    //This function expects a delta rotation in degrees. 
Mat4<float> DREAM::PhysicsSystem::GetRotatioMatrixfromRotation( float _deltaRotation, AXIS _rotationAxis)
{
	Mat4<float> result;
    
	_deltaRotation = _deltaRotation * (3.14159265358979323846 / 180.0); // Convert degrees to radians

	if (_rotationAxis == AXIS::X_AXIS)
	{
        result = Mat4<float>(
            Vec4<float>(1, 0, 0, 0),
            Vec4<float>(0, cos(_deltaRotation), -sin(_deltaRotation), 0),
            Vec4<float>(0, sin(_deltaRotation), cos(_deltaRotation), 0),
            Vec4<float>(0, 0, 0, 1));
	}
	else if (_rotationAxis == AXIS::Y_AXIS)
	{
        result = Mat4<float>(
            Vec4<float>(cos(_deltaRotation), 0, sin(_deltaRotation), 0),
            Vec4<float>(0, 1, 0, 0),
            Vec4<float>(-sin(_deltaRotation), 0, cos(_deltaRotation), 0),
            Vec4<float>(0, 0, 0, 1));
	}
	else if (_rotationAxis == AXIS::Z_AXIS)
	{
        result = Mat4<float>(
            Vec4<float>(cos(_deltaRotation), -sin(_deltaRotation), 0, 0),
            Vec4<float>(sin(_deltaRotation), cos(_deltaRotation), 0, 0),
            Vec4<float>(0, 0, 1, 0),
            Vec4<float>(0, 0, 0, 1));
	}
    return result;
}

Vec4<float> PhysicsSystem::GetEulerRotationfromRotationMatrix(const Mat4<float>& m)
{
    Vec4<float> euler;

    if (fabs(m.r3.x) < 1.0f)
    {
        euler.y = asinf(-m.r3.x); // pitch
        euler.x = atan2f(m.r3.y, m.r3.z); // roll
        euler.z = atan2f(m.r1.x, m.r2.x); // yaw
		euler.w = 0.0f; // w component is not used in this context, set to 0
    }
    else
    {
        // Gimbal lock at ±90 degrees
        euler.y = (m.r3.x < 0) ? (float)M_PI_2 : -(float)M_PI_2;
        euler.x = atan2f(-m.r1.z, m.r1.y);
        euler.z = 0.0f;
		euler.w = 0.0f; // w component is not used in this context, set to 0
    }

    return euler;
}

void PhysicsSystem::update()
{
    for (auto* tempEntity : entities)
    {
        //We will update the position based on velocity and rotation based on rotation (local rotation)
        PhysicsComponent* physicsComponent = tempEntity->getComponent<PhysicsComponent>();

        //Updating Position
        physicsComponent->position = physicsComponent->position + physicsComponent->velocity * (*dt_pointer);

        //Updating Rotation
        physicsComponent->rotation = physicsComponent->rotation + physicsComponent->rotation_velocity * (*dt_pointer);
    }
}

/*
* Returns rotation matrix from the provided physics component 
*/
Mat4<float> PhysicsSystem::GetModelMatrixfromComponent(PhysicsComponent* _physicsComponent)
{


    float rotation_x = _physicsComponent->rotation.x;
    float rotation_y = _physicsComponent->rotation.y;
    float rotation_z = _physicsComponent->rotation.z;

    Mat4<float> deltaRotationMatrix_x = PhysicsSystem::GetRotatioMatrixfromRotation(rotation_x, AXIS::X_AXIS);
    Mat4<float> deltaRotationMatrix_y = PhysicsSystem::GetRotatioMatrixfromRotation(rotation_y, AXIS::Y_AXIS);
    Mat4<float> deltaRotationMatrix_z = PhysicsSystem::GetRotatioMatrixfromRotation(rotation_z, AXIS::Z_AXIS);

    // Combine the delta rotation matrices
    Mat4<float> result = deltaRotationMatrix_z * deltaRotationMatrix_y * deltaRotationMatrix_x;


    //Finally set the positition of the camera to the physics component's position 
    result.r1.w = _physicsComponent->position.x;
    result.r2.w = _physicsComponent->position.y;
    result.r3.w = _physicsComponent->position.z;
    // The w component of the translation vector is set to 1 for homogeneous coordinates
    result.r4 = Vec4<float>(0, 0, 0, 1); // Last row for homogeneous coordinates

    return result;
}


}