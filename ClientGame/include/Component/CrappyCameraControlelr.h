#pragma once
#include <ECS_Core/Core.hpp>
#include <IEventHandler.hpp>

class CrappyCameraControlelr :
    public Component , public DREAM::IEventHandler
{
    int handleEvent(DREAM::EventInfo* _eventInfo) override;
};

