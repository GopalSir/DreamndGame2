#pragma once
#include "Entity.hpp"

class Component
{
    protected:

    //The entity to which this component belongs. 
    Entity* entity;
    public:
    void setEntity(Entity* _entity);
    virtual ~Component() = default;  // At least one virtual function
};