#include "../include/Component/PhysicsComponent.hpp"

namespace DREAM
{

PhysicsComponent::PhysicsComponent()
{
    position = {};
    velocity = {};
    rotation = {};


}

PhysicsComponent::PhysicsComponent(PhysicsComponent *_physicsComponent)
{
     position = _physicsComponent->position;
     velocity = _physicsComponent->velocity;
     rotation = _physicsComponent->rotation;
}

}