#pragma once
#include <ECS_Core/Core.hpp>
#include "../Vec3.hpp"

/* Still figuring out how to use this lol*/
class PhysicsComponent: public Component
{
  public:
  Vec4<float> velocity;
  Vec4<float> position;
  Vec4<float> rotation;
  Vec4<float> rotation_velocity;
  bool isGravity;
  bool isPhysics;

  PhysicsComponent();
  PhysicsComponent(Vec4<float> _velocity, Vec4<float> _position, Vec4<float> _rotation, Vec4<float> _rotationVelocity);
  PhysicsComponent(PhysicsComponent *_physicsComponent);

};