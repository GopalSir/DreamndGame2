#pragma once
#include <ECS_Core/Component.hpp>
#include <Vec3.hpp>

namespace DREAM
{

enum class ColliderType { BOX, PLANE };

/*
Collision shape, deliberately kept independent of the render mesh:
  - a visual cube is 36 vertices, a box collider is 3 floats
  - physics must still work with the renderer switched off (headless mode)
Lives in LOCAL space; the body's own transform supplies position and rotation.
*/
class ColliderComponent : public Component
{
public:
	ColliderType type = ColliderType::BOX;

	Vec3<float> half_extents = {1,1,1};   // BOX
	Vec3<float> normal       = {0,1,0};   // PLANE
	float       offset       = 0.0f;      // PLANE: dot(p, normal) == offset

	ColliderComponent(ColliderType _cd, Vec3<float> _he, Vec3<float> _normal, float _offset){
		type = _cd;
		half_extents = _he;
		normal = _normal;
		offset = _offset;
	}

};

struct Contact
{
	Entity* a;
	Entity* b;

	Vec3<float> point;
	Vec3<float> normal;

	float penetration_depth;
};

}
