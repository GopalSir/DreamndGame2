#pragma once
#include <ECS_Core/Component.hpp>
#include <Component/PhysicsComponent.hpp>
#include <ECS_Core/Entity.hpp>
#include <IEventHandler.hpp>
#include "../KeyStates.h"

namespace DREAM{
class CameraControllerComponent :public Component, public DREAM::IEventHandler
{
public:
	//Override:
	int handleEvent(DREAM::EventInfo* _eventInfo) override;
};

}