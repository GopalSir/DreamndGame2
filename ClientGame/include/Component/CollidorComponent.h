#pragma once
#include <ECS_Core/Component.hpp>

enum class ColliderType { BOX, PLANE};

class ColliderComponent : public Component
{
public:
	ColliderType type = ColliderType::BOX;
	Vec3<float> half_extents = {1,1,1};
	Vec3<float> normal = {0,1,0};
	float offset = 0.0f;

	ColliderComponent(ColliderType _cd, Vec3<float> _he, Vec3<float> _normal, float _offset){
		type = _cd;
		half_extents = _he;
		normal = _normal;
		offset = _offset;
	}

};

struct Contat
{
	Entity* a;
	Entity* b;

	Vec3<float> point;
	Vec3<float> normal;

	float penetration_depth;
};