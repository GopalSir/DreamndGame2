#include <ECS_Core/System.hpp>
#include <Component/PhysicsComponent.hpp>
#include <IEventHandler.hpp>
#include <KeyStates.h>
#include <System/PhysicsSystem.h>
#include "../../include/Component/CollidorComponent.h"


class CollisionSystem : public System
{
public:
    void update() override;

    

    /*This is called automatically when a an entity is added to this using 
    addEntity(Entity*) function. 
    */
    void onEntityAddition(Entity*) override;

  
};