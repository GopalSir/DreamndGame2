#pragma once 

#include "./Component/PhysicsComponent.hpp"
#include "./Component/PositionComponent.hpp"
#include "./Component/VerticesComponent.hpp"
#include "./ECS_Core/Log.hpp"
#include "./IEventHandler.hpp"
#include "./Shape.hpp"
#include "./System/CameraSystem.hpp"
#include "./System/RenderSystem.hpp"
#include <vector>



class ShapeCreator : public DREAM::IEventHandler
{
private:
	
	PhysicsComponent* cameraPhysicsComponent;
	DREAM::RenderSystem* renderSystem;
	DREAM::CameraComponent* cameraComponent;
	DREAM::VerticesComponent<float> vc;
	Vec4<float> previous_stw, current_stw;
	int draw_mode;
	void handle_draw_mode(DREAM::EventInfo* _eventInfo);
	void handle_clicks(DREAM::EventInfo* _eventInfo);

	//Counter to count number of clicks
	int click_counter;
	int first_point_planted;
	
public:
	int handleEvent(DREAM::EventInfo* _eventInfo) override;
	ShapeCreator(PhysicsComponent* _physicsComponent, DREAM::RenderSystem* _renderSystem, DREAM::CameraComponent* _cameraSystem);

};