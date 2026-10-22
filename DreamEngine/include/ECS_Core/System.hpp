#pragma once
#include <vector>
#include "Log.hpp"
#include "Entity.hpp"


//Forward declaration for infrastrucure which will be accessible to each sytem the moment it's registerd. 

namespace DREAM { class World; };

/* A system operates on Entities. It keeps a list of entities, */
class System
{
protected:
     DREAM::World*  world;

     //Called automatically from inside of //addEntity() function
     virtual void onEntityAddition(Entity*) {std::cout<<"Base System onEntityAddition called. This should be overridden in derived class"<<std::endl;};

    public:
    /*adds the entity to "entities" vector and then
    returns an integer to the index of the entity. */
    int addEntity(Entity*);

    
    std::vector<Entity*> entities;
    /*Get Entity*/
    Entity* getEntity(int _index); 

    /* Systems own behaviour, so they get to react to game tick every frame */
    virtual void update()=0;

    

    void setWorld( DREAM::World* const _world) { world = _world; };

    virtual ~System();
    
};