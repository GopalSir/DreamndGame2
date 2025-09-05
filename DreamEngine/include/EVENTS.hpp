#pragma once
#include "glheaders.hpp"

namespace DREAM
{
    class EventInfo
    {
        int eventTypeCode;
    public:
        int  getEventTypeCode() { return eventTypeCode; };
        EventInfo(int _eventTypeCode) { eventTypeCode = _eventTypeCode; };

        virtual ~EventInfo() {};


    };

    class KeyPressEvent :public EventInfo
    {
        static constexpr int localTypeCode = 1;
    public:
        int key_code;
        int action;

        KeyPressEvent() :EventInfo(localTypeCode) {};
        static int GetEventTypeCode() { return localTypeCode; };

    };

    class KeyReleaseEvent : public EventInfo
    {
        static constexpr int localTypeCode = 2;

    public:
        int key_code;
        int action;
        KeyReleaseEvent() :EventInfo(localTypeCode) {};
        static int GetEventTypeCode() { return localTypeCode; };
    };

    class WindowCloseEvent : public EventInfo
    {
        static constexpr int localTypeCode = 3;

    public:

        WindowCloseEvent() :EventInfo(localTypeCode) {};
        static int GetEventTypeCode() { return localTypeCode; };
    };

    class MouseClickEvent : public EventInfo
    {
        static constexpr int localTypeCode = 4;

    public:
        int key;
        int action;
        int mods;
        double x, y;
        MouseClickEvent() : EventInfo(localTypeCode) {};
        static int GetEventTypeCode() { return localTypeCode; };
   };

    class MouseScrollEvent : public EventInfo
    {
        static constexpr int localTypeCode = 5;
    public:
        double x_offset;
        double y_offset;
        MouseScrollEvent() : EventInfo(localTypeCode) {};
        static int GetEventTypeCode() { return localTypeCode; };
    };

}

//enum EVENTS
//{
//    //Game Events
//    GAME_INIT,
//    GAME_PAUSED,
//    GAME_EXIT,
//
//    //Movement Event
//    MOUSE_MOVED,
//    PLAYER_MOVED,
//    ENEMY_MOVED,
//
//    //Key Press EVENtS
//    KEY_PRESSED,
//    KEY_HOLD,
//    KEY_REMOVED,
//
//    //WINDOW Events
//    WINDOW_CLOSED
//};