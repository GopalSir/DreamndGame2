#include "MyGame.h"
#include "MyEvents.hpp"

DREAM::MyApplication* CreateApplication()
{
	return new MyGame();
}


MyGame::MyGame()
{
	Log::LogMessage("My Game constructor Called");

	int a = 10;

	ThrusterComponent* thrusterComponent = new ThrusterComponent();

	DREAM::EventSystem::registerEvent(PlaneCrashEvent::GetEventTypeCode(), thrusterComponent);

	if (a == 10)
	{

		PlaneCrashEvent* planeCrashEvent = new PlaneCrashEvent();
		DREAM::EventSystem::handleEvent(planeCrashEvent);
		delete planeCrashEvent;
	}
	

	Entity* basicCube = Shape::GetShape(Shape::SHAPE_TYPE::CUBE);
	


		int index1 = this->GetRenderSystem()->addEntity(basicCube);
		this->GetRenderSystem()->initEntityBuffers(index1);


	
}



