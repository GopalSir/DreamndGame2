#pragma once 

#include "./IEventHandler.hpp"
#include "./ECS_Core/Log.hpp"
#include "./Component/PositionComponent.hpp"
#include "./Component/PhysicsComponent.hpp"
#include "./System/RenderSystem.hpp"
#include "./System/CameraSystem.hpp"
#include "./Shape.hpp"
#include <vector>



class ShapeCreator : public DREAM::IEventHandler
{
private:
	
	PhysicsComponent* cameraPhysicsComponent;
	DREAM::RenderSystem* renderSystem;
	DREAM::CameraComponent* cameraComponent;
	std::vector<PositionComponent<float>> points;
	Vec4<float> previous_stw, current_stw;
	
public:
	int handleEvent(DREAM::EventInfo* _eventInfo) override;
	ShapeCreator(PhysicsComponent* _physicsComponent, DREAM::RenderSystem* _renderSystem, DREAM::CameraComponent* _cameraSystem);

};