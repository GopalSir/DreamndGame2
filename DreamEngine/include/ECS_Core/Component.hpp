#pragma once

class Entity;  // Forward declaration

class Component
{
    protected:

    //The entity to which this component belongs. 
    Entity* entity;
    public:
    void setEntity(Entity* _entity);
    virtual ~Component() = default;  // At least one virtual function
	virtual void doPostConstruct() {
		// Default implementation does nothing, can be overridden by derived classes
	}
};