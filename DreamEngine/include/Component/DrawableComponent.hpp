#pragma once
#include <ECS_Core/Core.hpp>
#include "../glheaders.hpp"


class DrawableComponent: public Component
{
    public:
    GLuint VBO;
    GLuint VAO;
};