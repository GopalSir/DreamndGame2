#pragma once
#include <ECS_Core/Core.hpp>
#include "PositionComponent.hpp"
#include "Colors.h"
#include <Component/VertexAttribComponent.hpp>



namespace DREAM
{
    template<typename T>
    class VerticesComponent : public Component
    {
    public:
        std::vector<PositionComponent<T>> vertices;
        std::vector<COLOR>vertices_color;
        std::vector<PositionComponent<T>> normals;

        std::vector<VertexAttribPointer*> vertexAttributePointers;
    };

}