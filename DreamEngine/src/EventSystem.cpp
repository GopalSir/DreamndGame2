#include "../include/System/EventSystem.hpp"
namespace DREAM
{
    void EventSystem::registerEvent(int _eventKeyCode, IEventHandler* _IeventHandler)
    {
        event_map[_eventKeyCode].push_back(_IeventHandler);
    }

    void EventSystem::handleEvent(EventInfo* _event_info)
    {
        int eventTypeCode = _event_info->getEventTypeCode();
        Log::LogMessage("Event Code" + std::to_string(eventTypeCode));

        for (auto f : event_map[eventTypeCode])
        {
            f->handleEvent(_event_info);
        }


    }

    //void EventSystem::handleEvent(EVENTS _event_type,EventInfo* _event_info)
    //{
    //    Log::LogMessage("Listener Type " + std::to_string(event_map[_event_type].size()));
    //
    //    Log::LogMessage("Listener count: " + std::to_string(event_map[_event_type].size()));
    //    for(auto f: event_map[_event_type])
    //    {
    //        f->handleEvent(_event_type,_event_info);
    //    }
    //}


    //EventSystem* EventSystem::getInstance()
    //{
    //    if(has_instance == false)
    //    {
    //        instance = new EventSystem();
    //        has_instance = true;
    //        return instance;
    //    }
    //    else
    //    {
    //        return instance;
    //    }
    //
    //}

    //bool EventSystem::has_instance = false;
    //EventSystem* EventSystem::instance = nullptr;
    std::map<int, std::vector<IEventHandler*>> EventSystem::event_map = {};
}