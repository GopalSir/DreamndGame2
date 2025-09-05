#include "CameraControllerComponent.h"

namespace DREAM
{
	CameraControllerComponent::CameraControllerComponent()
	{
		cameraComponent = nullptr;
		physicsComponent = nullptr;
		Log::LogMessage("CameraControllerComponent Constructor Called", LogLevel::INFO_LEVEL);

	}
    void CameraControllerComponent::doPostConstruct() {
        Log::LogMessage("CameraControllerComponent PostConstruct Called", LogLevel::INFO_LEVEL);

		cameraComponent = this->entity->getComponent<CameraComponent>();
		physicsComponent = this->entity->getComponent<PhysicsComponent>();
        if (physicsComponent == nullptr)
        {
            Log::LogMessage("Physics Component is null in CameraControllerComponent", LogLevel::ERROR_LEVEL);
        }
		if (cameraComponent == nullptr)
		{
			Log::LogMessage("Camera Component is null in CameraControllerComponent", LogLevel::ERROR_LEVEL);
		}
    }

    int CameraControllerComponent::handleEvent(DREAM::EventInfo* _eventInfo)
    {
		//std::cout<<"camera controller event boo"<<std::flush;
        
        Vec3<float> x_axis(cameraComponent->cameraWorldTransform.r1.x, cameraComponent->cameraWorldTransform.r2.x, cameraComponent->cameraWorldTransform.r3.x);
        Vec3<float> y_axis(cameraComponent->cameraWorldTransform.r1.y, cameraComponent->cameraWorldTransform.r2.y, cameraComponent->cameraWorldTransform.r3.y);
        Vec3<float> z_axis(cameraComponent->cameraWorldTransform.r1.z, cameraComponent->cameraWorldTransform.r2.z, cameraComponent->cameraWorldTransform.r3.z);
        // Normalize the axes to ensure they are unit vectors
        x_axis = Vec3<float>::normalize(x_axis);
        y_axis = Vec3<float>::normalize(y_axis);
        z_axis = Vec3<float>::normalize(z_axis);

        //check if camera active

        if (_eventInfo->getEventTypeCode() == DREAM::KeyPressEvent::GetEventTypeCode())
        {


			if (DREAM::KeyStates::KeyState[GLFW_KEY_LEFT_CONTROL].first == true && DREAM::KeyStates::KeyState[GLFW_KEY_RIGHT].first == true)
			{
				//std::cout << "Left Control and right arrow Pressed" << std::endl;
                //now we add to rotational speed around the flat axis of the camera. 
                
                //Mat3<float> x_axis = 
				//physicsComponent->rotation_velocity = Vec4<float>(0, 0.1, 0, 0);
                physicsComponent->rotation_velocity = Vec4<float>(0,-100.0f,0,0);


			}
            else if (DREAM::KeyStates::KeyState[GLFW_KEY_LEFT_CONTROL].first == true && DREAM::KeyStates::KeyState[GLFW_KEY_LEFT].first == true)
            {
                //std::cout << "Left Control and left arrow Pressed" << std::endl;
                //now we add to rotational speed around the flat axis of the camera. 


                physicsComponent->rotation_velocity = Vec4<float>(0, 100.0f, 0, 0);

            }
            else if (DREAM::KeyStates::KeyState[GLFW_KEY_LEFT_CONTROL].first == true && DREAM::KeyStates::KeyState[GLFW_KEY_UP].first == true)
            {
                //std::cout << "Left Control and up arrow Pressed" << std::endl;
                //now we add to rotational speed around the flat axis of the camera. 
                //for now let's experiment with global-y rotation
                physicsComponent->rotation_velocity = Vec4<float>(100.0f, 0, 0, 0);


            }
            else if (DREAM::KeyStates::KeyState[GLFW_KEY_LEFT_CONTROL].first == true && DREAM::KeyStates::KeyState[GLFW_KEY_DOWN].first == true)
            {
                //std::cout << "Left Control and down arrow Pressed" << std::endl;
                //now we add to rotational speed around the flat axis of the camera. 
                //for now let's experiment with global-y rotation
                physicsComponent->rotation_velocity = Vec4<float>(-100.0f, 0, 0, 0);


            }
            
            else if (DREAM::KeyStates::KeyState[GLFW_KEY_A].first == true)
                        {
                            // Move left locally, aka left of whereever youre looking. 
                            Vec3<float> x_axis(cameraComponent->cameraWorldTransform.r1.x, cameraComponent->cameraWorldTransform.r2.x, cameraComponent->cameraWorldTransform.r3.x);
                            x_axis = Vec3<float>::normalize(x_axis);
							physicsComponent->velocity = Vec4<float>(-x_axis.x * 100, -x_axis.y * 100, -x_axis.z * 100, 0);

                        }
            else  if (DREAM::KeyStates::KeyState[GLFW_KEY_D].first == true)
                        {
                            // Move right
                            // Move left locally, aka left of whereever youre looking. 

							physicsComponent->velocity = Vec4<float>(x_axis.x * 100, x_axis.y * 100, x_axis.z * 100, 0);
                            
                        }
            else if (DREAM::KeyStates::KeyState[GLFW_KEY_S].first == true)
                        {
                            // Move up
                if (DREAM::KeyStates::KeyState[GLFW_KEY_LEFT_CONTROL].first == false)
                {
					//S pressed and left control not pressed, so we move down
                    //std::cout << "Panning down" << std::endl;
                    physicsComponent->velocity = Vec4<float>(-y_axis.x * 50, -y_axis.y * 50, -y_axis.z * 50, 0);
                    
                }
                else
                {
                    //Zoom Out
                    physicsComponent->velocity = Vec4<float>(z_axis.x * 100, z_axis.y * 100, z_axis.z * 100, 0);
                    
                }
                        }
            else if (DREAM::KeyStates::KeyState[GLFW_KEY_W].first == true)
                        {
                            // Move u
                if (DREAM::KeyStates::KeyState[GLFW_KEY_LEFT_CONTROL].first == false)
                {
                    //std::cout << "Panning up" << std::endl;
                    physicsComponent->velocity = Vec4<float>(y_axis.x * 50, y_axis.y * 50, y_axis.z * 50, 0);
                }
                            else
                            {
                    //Zoom Out
                    physicsComponent->velocity = Vec4<float>(-z_axis.x * 100, -z_axis.y * 100, -z_axis.z * 100, 0);
								
                            }


                        }
                        if (DREAM::KeyStates::KeyState[GLFW_KEY_E].first == true)
                        {
                            physicsComponent->rotation_velocity = Vec4<float>(0, 0, -100.f, 0);

                        }
                        if (DREAM::KeyStates::KeyState[GLFW_KEY_Q].first == true)
                        {
                            physicsComponent->rotation_velocity = Vec4<float>(0, 0, 100.f, 0);
                        }
                    
                

            
        }
        else if (_eventInfo->getEventTypeCode() == DREAM::KeyReleaseEvent::GetEventTypeCode())
        {
            // std::cout<<"key removed boo"<<std::endl;
            if (DREAM::KeyStates::KeyState[GLFW_KEY_LEFT_CONTROL].first == false || DREAM::KeyStates::KeyState[GLFW_KEY_RIGHT].first == false)
            {
                //std::cout << "Left Control and right arrow Released" << std::endl;
                //now we add to rotational speed around the flat axis of the camera. 
                //for now let's experiment with global-y rotation
                physicsComponent->rotation_velocity = Vec4<float>(0, 0, 0, 0);


            }
           
                        if (physicsComponent == nullptr)
                        {
                            //std::cout << "Physics Componenet null in release event ";
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
                //std::cout << "Left Button Pressed\n";
            }
            else if (mouseClickEvent->key == GLFW_MOUSE_BUTTON_RIGHT)
            {
                //std::cout << "Right Button Pressed\n";
            }
            //std::cout << "Mouse Clicked at position: (" << mouseClickEvent->x << ", " << mouseClickEvent->y << ")\n";

        }
        else if (_eventInfo->getEventTypeCode() == DREAM::MouseScrollEvent::GetEventTypeCode())
        {
            MouseScrollEvent* mouseScrollEvent = dynamic_cast<MouseScrollEvent*>(_eventInfo);
            std::cout << "Y Scroll: " << mouseScrollEvent->y_offset << "\n";
            Vec4<float> position_offset = Vec4<float>(z_axis.x * 10, z_axis.y * 10, z_axis.z * 10, 1) * (-mouseScrollEvent->y_offset);
            position_offset.w = 1;
        
            physicsComponent->position = physicsComponent->position + position_offset;
            physicsComponent->position.w = 1;

           

            }
        return 0;
    }
}