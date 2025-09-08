#include "../include/Component/PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent()
{
    position = {};
    velocity = {};
    rotation = {};


}

PhysicsComponent::PhysicsComponent(Vec4<float> _velocity, Vec4<float> _position, Vec4<float> _rotation, Vec4<float> _rotationVelocity)
{
    velocity = _velocity;
    position = _position;
    rotation = _rotation;
    rotation_velocity = _rotationVelocity;
}


PhysicsComponent::PhysicsComponent(PhysicsComponent *_physicsComponent)
{
     position = _physicsComponent->position;
     velocity = _physicsComponent->velocity;
     rotation = _physicsComponent->rotation;
}