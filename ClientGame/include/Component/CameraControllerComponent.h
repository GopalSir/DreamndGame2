#pragma once
#include <ECS_Core/Component.hpp>
#include <Component/PhysicsComponent.hpp>
#include <Component/CameraComponent.h>
#include <System/PhysicsSystem.h>
#include <ECS_Core/Entity.hpp>
#include <IEventHandler.hpp>
#include <KeyStates.h>

namespace DREAM{
class CameraControllerComponent :public Component, public DREAM::IEventHandler
{
private:
	PhysicsComponent* physicsComponent;
	CameraComponent* cameraComponent;

	bool right_mouse_buttton_status;
	bool mouse_moved;

	MouseClickEvent lastClickEvent;
	

	void HandleRMBdrag();

public:
	//Override:
	int handleEvent(DREAM::EventInfo* _eventInfo) override;
	void doPostConstruct() override;

	Mat4<float> lookAroundDeltaRotationMatrix;

	//Constructor
	CameraControllerComponent();
};

}