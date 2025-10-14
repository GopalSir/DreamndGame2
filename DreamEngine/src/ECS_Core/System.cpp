#include "../../include/ECS_Core/System.hpp"


int System::addEntity(Entity* _entity)
{
    entities.push_back(_entity);
    return entities.size()-1;
}

Entity* System::getEntity(int _index)
{
    if(_index < 0 || _index >= (entities.size()))
    {
        Log::LogMessage("Invalid entity index in System::getEntity()",LogLevel::ERROR_LEVEL);
        exit(0);
    }
    else
    {
        return entities[_index];
    }
};

System::~System()
{
    std::cout << "Calling Base Destructor";
    //When a system is destroyed, it needs to destroy all entities it was pointing too. 
    for (auto* tmpEntity : entities)
    {
        delete tmpEntity;
    }

}
