#include <EVENTS.hpp>

#define DEFINE_EVENT(EventClassName,EventTypeCode) \
        private: static constexpr int localTypeCode = EventTypeCode;	\
public:EventClassName() :EventInfo(localTypeCode) {};		\
 static int GetEventTypeCode() { return localTypeCode; };	\





class PlaneCrashEvent : public DREAM::EventInfo
{
	std::string airplaneName;

	DEFINE_EVENT(PlaneCrashEvent, 21);
};

class 