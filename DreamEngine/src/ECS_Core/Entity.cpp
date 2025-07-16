#include "../../include/ECS_Core/Entity.hpp"
#include "../../include/ECS_Core/Component.hpp"

int Entity::getEntity()
{
    return entityID;
}

void Entity::addComponent(Component* _component)
{
    _component->setEntity(this);
    components.push_back(_component);
    
}