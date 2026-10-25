#pragma once
#include <ECS_Core/System.hpp>
#include <Component/PhysicsComponent.hpp>
#include <Component/CollidorComponent.h>
#include <System/PhysicsSystem.h>

namespace DREAM
{

/*
Detects and resolves contacts. Runs AFTER PhysicsSystem has integrated, so it
is correcting where bodies actually moved to rather than where they were.
*/
class CollisionSystem : public System
{
public:
    void update() override;

    /*This is called automatically when a an entity is added to this using
    addEntity(Entity*) function.
    */
    void onEntityAddition(Entity*) override;

};

}
