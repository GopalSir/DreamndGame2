#pragma once
#include <vector>
#include "Log.hpp"
#include "Entity.hpp"


/* A system operates on Entities. It keeps a list of entities, */
class System
{
    /*Vector to store collection of Entities*/



    public:
    /*adds the entity to "entities" vector and then
    returns an integer to the index of the entity. */
    int addEntity(Entity*);
    std::vector<Entity*> entities;
    /*Get Entity*/
    Entity* getEntity(int _index); 

    /* Still thinking what to do with this*/
    virtual void update()=0;
    // virtual void update(int _index)=0;
    // virtual void update(std::vector<int> _index_vector);
    
};