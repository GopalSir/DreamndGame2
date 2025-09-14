#pragma once
#include <ECS_Core/Core.hpp>
#include <Component/PhysicsComponent.hpp>
#include "./../Component/CrappyBirdComponent.h"
#include <Shape.hpp>
#include <System/RenderSystem.hpp>

class CrappyBirdSystem : public System
{
private:
	Entity* GeneratePillar(int _r_limit,int _y_limit, int _dir, int _width, int _height);
	void CheckPillarCondition();
public:
	CrappyBirdSystem();

	void update() override;
	void SetBirdEntityIndex(int _index);
	int bird_entity_index;

};

