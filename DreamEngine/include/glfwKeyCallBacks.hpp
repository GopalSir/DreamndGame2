#pragma once
#include "System/EventSystem.hpp"
#include "glheaders.hpp"
#include "../KeyStates.h"

namespace DREAM
{
	void GLFW_KeyPress_Callback_Handler(GLFWwindow* _window, int key, int scancode, int action, int mods);
	//void GLFW_WindowClose_Callback_Handler(GLFWwindow* _window);
	void GLFW_WindowResize_Callback_Handler(GLFWwindow* _window, int _width, int _height);
	void GLFW_Scroll_Callback_Handler(GLFWwindow* , double _xOffset, double _yOffset);

}