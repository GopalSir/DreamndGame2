#pragma once
#include <ECS_Core/Core.hpp>
#include "../Component/PhysicsComponent.hpp"
#include "../Component/DrawableComponent.hpp"
#include "../Component/VertexAttribComponent.hpp"
#include "../Component/VerticesComponent.hpp"
#include "../VertexAttribPointerGenerator.hpp"

using namespace DREAM;
class RectangleEntity : public Entity
{
    public:
    RectangleEntity(float _x, float _y, float _length,float _breadth);
};