#include "CameraControllerComponent.h"

namespace DREAM
{

    int CameraControllerComponent::handleEvent(DREAM::EventInfo* _eventInfo)
    {
		std::cout<<"camera controller event boo"<<std::flush;
        PhysicsComponent* physicsComponent = this->entity->getComponent<PhysicsComponent>();

        //check if camera active

        if (_eventInfo->getEventTypeCode() == DREAM::KeyPressEvent::GetEventTypeCode())
        {
                        

                        if (DREAM::KeyStates::KeyState[GLFW_KEY_A].first == true)
                        {
                            // Move left
                            physicsComponent->velocity = Vec4<float>(-40, 0, 0, 0);

                        }
                        if (DREAM::KeyStates::KeyState[GLFW_KEY_D].first == true)
                        {
                            // Move right
                            physicsComponent->velocity.x = 40.0f;
                        }
                        if (DREAM::KeyStates::KeyState[GLFW_KEY_S].first == true)
                        {
                            // Move up
                            if (DREAM::KeyStates::KeyState[GLFW_KEY_LEFT_CONTROL].first == false)
                                physicsComponent->velocity = Vec4<float>(0, -40, 0, 0);
                            else
                                physicsComponent->velocity = Vec4<float>(0, 0, -1, 0);
                        }
                        if (DREAM::KeyStates::KeyState[GLFW_KEY_W].first == true)
                        {
                            // Move u
                            if (DREAM::KeyStates::KeyState[GLFW_KEY_LEFT_CONTROL].first == false)
                                physicsComponent->velocity = Vec4<float>(0, 40, 0, 0);
                            else
                                physicsComponent->velocity = Vec4<float>(0, 0, 1, 0);


                        }
                        if (DREAM::KeyStates::KeyState[GLFW_KEY_E].first == true)
                        {
                            // Move up

                            physicsComponent->rotation_velocity = Vec4<float>(0, 0, 10, 0);
                            physicsComponent->rotation_velocity.x = (22.0 / (7 * 180)) * physicsComponent->rotation_velocity.x;
                            physicsComponent->rotation_velocity.y = (22.0 / (7 * 180)) * physicsComponent->rotation_velocity.y;
                            physicsComponent->rotation_velocity.z = (22.0 / (7 * 180)) * physicsComponent->rotation_velocity.z;
                        }
                        if (DREAM::KeyStates::KeyState[GLFW_KEY_Q].first == true)
                        {
                            // Move up
                            physicsComponent->rotation_velocity = Vec4<float>(0, 0, -10, 0);
                            physicsComponent->rotation_velocity.x = (22.0 / (7 * 180)) * physicsComponent->rotation_velocity.x;
                            physicsComponent->rotation_velocity.y = (22.0 / (7 * 180)) * physicsComponent->rotation_velocity.y;
                            physicsComponent->rotation_velocity.z = (22.0 / (7 * 180)) * physicsComponent->rotation_velocity.z;
                        }
                    
                

            
        }
        else if (_eventInfo->getEventTypeCode() == DREAM::KeyReleaseEvent::GetEventTypeCode())
        {
            // std::cout<<"key removed boo"<<std::endl;
           
                        if (physicsComponent == nullptr)
                        {
                            std::cout << "Physics Componenet null in release event ";
                        }
                        if (DREAM::KeyStates::KeyState[GLFW_KEY_A].first == false)
                        {
                            // Move left
                            physicsComponent->velocity = Vec4<float>(0, 0, 0, 0);
                        }
                        if (DREAM::KeyStates::KeyState[GLFW_KEY_D].first == false)
                        {
                            // Move right
                            physicsComponent->velocity = Vec4<float>(0, 0, 0, 0);
                        }
                        if (DREAM::KeyStates::KeyState[GLFW_KEY_S].first == false)
                        {
                            // Move down
                            physicsComponent->velocity = Vec4<float>(-0, 0, 0, 0);
                        }
                        if (DREAM::KeyStates::KeyState[GLFW_KEY_W].first == false)
                        {
                            // Move up
                            physicsComponent->velocity = Vec4<float>(0, 0, 0, 0);

                        }
                        if (DREAM::KeyStates::KeyState[GLFW_KEY_E].first == false)
                        {
                            // Move up
                            physicsComponent->rotation_velocity = Vec4<float>(0, 0, 0, 0);
                        }
                        if (DREAM::KeyStates::KeyState[GLFW_KEY_Q].first == false)
                        {
                            // Move up
                            physicsComponent->rotation_velocity = Vec4<float>(0, 0, 0, 0);
                        }
                    
                

            
        }
        else if (_eventInfo->getEventTypeCode() == DREAM::MouseClickEvent::GetEventTypeCode())
        {
            MouseClickEvent* mouseClickEvent = dynamic_cast<MouseClickEvent*>(_eventInfo);

            if (mouseClickEvent->key == GLFW_MOUSE_BUTTON_LEFT)
            {
                std::cout << "Left Button Pressed\n";
            }
            else if (mouseClickEvent->key == GLFW_MOUSE_BUTTON_RIGHT)
            {
                std::cout << "Right Button Pressed\n";
            }
            std::cout << "Mouse Clicked at position: (" << mouseClickEvent->x << ", " << mouseClickEvent->y << ")\n";

        }
        return 0;
    }
}