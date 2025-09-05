#include "../include/glfwKeyCallBacks.hpp"

namespace DREAM
{

    void GLFW_KeyPress_Callback_Handler(GLFWwindow* _window, int key, int scancode, int action, int mods)

    {
        if (action == GLFW_PRESS)
        {
            KeyPressEvent* _tempKeyPressInfo = new KeyPressEvent();
            //_tempKeyPressInfo->key_code = key;
            //_tempKeyPressInfo->action = 0; // don't care for now

            
            KeyStates::setState(key, std::pair<bool, bool>(true, false));

            EventSystem::handleEvent(_tempKeyPressInfo);
            
        }
        else if(action == GLFW_REPEAT)
            
            {
                KeyPressEvent* _tempKeyPressInfo = new KeyPressEvent();
                //_tempKeyPressInfo->key_code = key;
                //_tempKeyPressInfo->action = 0; // don't care for now


                KeyStates::setState(key, std::pair<bool, bool>(true, true));

                EventSystem::handleEvent(_tempKeyPressInfo);

            }
        else if (action == GLFW_RELEASE)
        {
            KeyReleaseEvent* _tempKeyReleaseInfo = new KeyReleaseEvent();
            //_tempKeyReleaseInfo->key_code = key;
            //_tempKeyReleaseInfo->action = 0; // don't care for now

            KeyStates::setState(key, std::pair<bool, bool>(false, false));


            EventSystem::handleEvent( _tempKeyReleaseInfo);
            
        }
    }

    void GLFW_WindowClose_Callback_Handler(GLFWwindow* _window)
    {
        WindowCloseEvent* windowCloseEvent = new WindowCloseEvent();
        EventSystem::handleEvent(windowCloseEvent);

    }

    void GLFW_WindowResize_Callback_Handler(GLFWwindow* _window, int _width, int _height)
    {
        int *a, *b;
        a = new int;
        b = new int;
        glfwGetFramebufferSize(_window, a, b);
        std::cout << "Framebuffer size before resize: " << *a << " " << *b << std::endl;
        std::cout << "Window Resized\n";
        
        //glfwSetWindowSize(_window, _width, _height);
        glViewport(0, 0, _width, _height);
        glfwGetFramebufferSize(_window, a, b);
        std::cout << "Framebuffer size after resize: " << *a << " " << *b << std::endl;

    }

    void GLFW_Scroll_Callback_Handler(GLFWwindow*, double _xOffset, double _yOffset)
    {
        MouseScrollEvent* mouseScrollEvent = new MouseScrollEvent();
        mouseScrollEvent->x_offset = _xOffset;
        mouseScrollEvent->y_offset = _yOffset;

        EventSystem::handleEvent(mouseScrollEvent);
    }

}