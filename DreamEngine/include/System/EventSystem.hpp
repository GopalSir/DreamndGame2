// singleteon class with function wrappers
#pragma once
#include <ECS_Core/Core.hpp>
#include "../EVENTS.hpp"
#include "../IEventHandler.hpp"
#include <functional>
#include <map>


namespace DREAM {

    class EventSystem
    {


        static std::map<int, std::vector<IEventHandler*>> event_map;
    public:

        //Singleton approach
        //static EventSystem* getInstance();
        static void registerEvent(int _eventKeyCode, IEventHandler* _IeventHandler);
        //static void handleEvent(EVENTS _event_type,EventInfo* _event_info);
        static void handleEvent(EventInfo* _event_info);

    };
}
