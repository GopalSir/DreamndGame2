#include <ECS_Core/Core.hpp>
#include <IEventHandler.hpp>

class ThrusterComponent : public Component, public DREAM::IEventHandler
{
public :
	int thrust;
	int handleEvent(DREAM::EventInfo*) override;

};