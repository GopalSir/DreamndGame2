#pragma once
#include <ECS_Core/Core.hpp>
#include "PositionComponent.hpp"

template<typename T>
class VerticesComponent: public Component
{
    public:
    std::vector<PositionComponent<T>> vertices;
};  