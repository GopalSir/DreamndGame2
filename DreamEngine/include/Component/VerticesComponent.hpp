#pragma once
#include <ECS_Core/Core.hpp>
#include "PositionComponent.hpp"
#include "Colors.h"

namespace DREAM
{
    template<typename T>
    class VerticesComponent : public Component
    {
    public:
        std::vector<PositionComponent<T>> vertices;
        std::vector<COLOR>vertices_color;
    };

}