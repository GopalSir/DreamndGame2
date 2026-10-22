#pragma once
#include <ECS_Core/Core.hpp>
#include "../Vec3.hpp"


namespace DREAM
{

/* Still figuring out how to use this lol*/
class PhysicsComponent: public Component
{
  
	// PhysicsComponent is used to store the physics related information of an entity.
  public:
  
  float mass= 1.0f; // Default mass is 1.0f, can be set to any value
  Vec4<float> force = {0.0f, 0.0f, 0.0f, 1.0f}; // Default force is zero, can be set to any value

  Vec4<float> velocity = {0.0f, 0.0f, 0.0f, 1.0f}; // Default velocity is zero, can be set to any value
  Vec4<float> position = {0.0f, 0.0f, 0.0f, 1.0f}; // Default position is zero, can be set to any value

  Vec4<float> rotation = {0.0f, 0.0f, 0.0f, 1.0f}; // Default rotation is zero, can be set to any value
  Vec4<float> rotation_velocity = {0.0f, 0.0f, 0.0f, 1.0f}; // Default rotation velocity is zero, can be set to any value

  // These are read every frame by PhysicsSystem::update() but no constructor assigned
  // them, so an entity's gravity was whatever happened to be on the heap. Defaulted
  // here: opt in to gravity explicitly rather than inheriting garbage.
  bool isGravity = false;
  bool isPhysics = true;

  PhysicsComponent();
  PhysicsComponent(Vec4<float> _velocity, Vec4<float> _position, Vec4<float> _rotation, Vec4<float> _rotationVelocity){
    
    velocity = _velocity;
    position = _position;
    rotation = _rotation;
    rotation_velocity = _rotationVelocity;
  } ;
  PhysicsComponent(PhysicsComponent *_physicsComponent);
  
  



};
}