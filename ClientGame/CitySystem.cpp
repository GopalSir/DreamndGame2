#include "CitySystem.h"

CitySystem::CitySystem()
{
	 mCityGenerator = new CityGenerator();

}

void CitySystem::update()
{
	 //
	//std::cout << "City system updating";
}

int CitySystem::handleEvent(DREAM::EventInfo* _eventInfo)
{
	if (_eventInfo->getEventTypeCode() == DREAM::MouseClickEvent::GetEventTypeCode())
	{
		DREAM::MouseClickEvent* mc = dynamic_cast<DREAM::MouseClickEvent*>(_eventInfo);

		if (mc->action == GLFW_RELEASE)
		{
			return 0;
		}

		Entity* tempEntity = mCityGenerator->GetCity();
		int tempint = world->renderSystem->addEntity(tempEntity);
		world->renderSystem->initEntityBuffers(tempint);
		

	}
	std::cout << "Recieved mouseclick in CitySystem";

	return 0;
}
