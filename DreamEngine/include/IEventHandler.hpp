#pragma once
#include "EVENTS.hpp"

namespace DREAM {
    class IEventHandler
    {
    public:
        virtual int  handleEvent(EventInfo* _eventInfo) =0;
    };
}