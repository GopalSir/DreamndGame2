#pragma once
#include <ECS_Core/Core.hpp>
#include "../glheaders.hpp"

class WindowComponent: public Component
{
    public:
    GLFWwindow* glfwWindow;
};