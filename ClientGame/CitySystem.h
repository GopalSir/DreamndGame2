#pragma once
#include <ECS_Core/Core.hpp>
#include <IEventHandler.hpp>
#include "CityGenerator.h"
#include <World.h>

class CitySystem: public System, public DREAM::IEventHandler
{
	CityGenerator* mCityGenerator;

public :
	CitySystem();
	void update() override;
	int handleEvent(DREAM::EventInfo* _eventInfo);
};

