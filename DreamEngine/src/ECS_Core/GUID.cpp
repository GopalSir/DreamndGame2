#include "../../include/ECS_Core/GUID.hpp"

namespace DREAM{
    unsigned int GetGUID(unsigned int _initCounter,bool _reset)
    {
    
    
        static unsigned int GUID =0;

        if(_reset == true)
        {
            GUID = ++_initCounter;
        }

        return ++GUID;
    }
}