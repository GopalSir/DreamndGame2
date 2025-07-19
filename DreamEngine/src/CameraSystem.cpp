#include "../include/System/CameraSystem.hpp"
namespace DREAM
{
    void CameraSystem::update()
    {
        // Iterate over all entities managed by the system
        for (auto* tempEntity : entities)
        {

            //We'll only update view matrices here. 
            CameraComponent* cameraComponent = tempEntity->getComponent<CameraComponent>();
            if (cameraComponent == nullptr)
            {
                Log::LogMessage("null camera returned in CameraSystem Update", LogLevel::ERROR_LEVEL);
            }
            else
            {
                cameraComponent->calculateViewMatrix();
                cameraComponent->CalculateProjectionMatrix();
                cameraComponent->CalculateMVP();
            }
            


     //       // Check if the entity is a CameraEntity and is active
     //       CameraEntity* tempCameraEntity = dynamic_cast<CameraEntity*>(tempEntity);
     //       if (tempCameraEntity && tempCameraEntity->active)
     //       {
     //           // Get the PhysicsComponent of the CameraEntity
     //           PhysicsComponent* physicsComponent = tempCameraEntity->getComponent<PhysicsComponent>();
     //           MVPComponent* mvpComponent = tempCameraEntity->getComponent<MVPComponent>();
     //           if (physicsComponent)
     //           {

     //               // Update the position using the velocity
     //               physicsComponent->position.x -= physicsComponent->velocity.x;
     //               physicsComponent->position.y -= physicsComponent->velocity.y;
     //               physicsComponent->position.z -= physicsComponent->velocity.z;
     //               physicsComponent->position.w = 1; // Usually w remains unchanged

     //               physicsComponent->rotation.x -= physicsComponent->rotation_velocity.x;
     //               physicsComponent->rotation.y -= physicsComponent->rotation_velocity.y;
     //               physicsComponent->rotation.z -= physicsComponent->rotation_velocity.z;
     //               physicsComponent->rotation.w -= 0;

     //               mvpComponent->setRotation(physicsComponent->rotation.x,
     //                   physicsComponent->rotation.y,
     //                   physicsComponent->rotation.z);

     //               mvpComponent->setPosition(physicsComponent->position.x,
     //                   physicsComponent->position.y,
     //                   physicsComponent->position.z);

     //               float fov = 45.0f * (3.1415926f / 180.0f);

					//int windowWidth, windowHeight;
					//GLFWwindow* currentWindow = glfwGetCurrentContext();
					//glfwGetFramebufferSize(currentWindow, &windowWidth, &windowHeight);

     //               float aspect = (float)windowWidth / windowHeight;
     //               float near = 0.1f;
     //               float far =300.0f;

     //               Mat4<float> projMatrix = MVPComponent::CreatePerspective(fov, aspect, near, far);
					//mvpComponent->setPerspective(projMatrix);

     //               Mat4<float> tempMVP = mvpComponent->getMVP();

     //               //Logging MVP
					//std::cout << tempMVP.r1.x << " " << tempMVP.r1.y << " " << tempMVP.r1.z << " " << tempMVP.r1.w << "\n";
					//std::cout << tempMVP.r2.x << " " << tempMVP.r2.y << " " << tempMVP.r2.z << " " << tempMVP.r2.w << "\n";
					//std::cout << tempMVP.r3.x << " " << tempMVP.r3.y << " " << tempMVP.r3.z << " " << tempMVP.r3.w << "\n";
					//std::cout << tempMVP.r4.x << " " << tempMVP.r4.y << " " << tempMVP.r4.z << " " << tempMVP.r4.w << "\n";
					///*std::cout << mvpComponent->getPerspective().r1.x << " " << mvpComponent->getPerspective().r1.y << " " << mvpComponent->getPerspective().r1.z << " " << mvpComponent->getPerspective().r1.w << "\n";
					//std::cout << mvpComponent->getPerspective().r2.x << " " << mvpComponent->getPerspective().r2.y << " " << mvpComponent->getPerspective().r2.z << " " << mvpComponent->getPerspective().r2.w << "\n";
					//std::cout << mvpComponent->getPerspective().r3.x << " " << mvpComponent->getPerspective().r3.y << " " << mvpComponent->getPerspective().r3.z << " " << mvpComponent->getPerspective().r3.w << "\n";
					//std::cout << mvpComponent->getPerspective().r4.x << " " << mvpComponent->getPerspective().r4.y << " " << mvpComponent->getPerspective().r4.z << " " << mvpComponent->getPerspective().r4.w << "\n";*/

     //               shader->setUniform("mvp", tempMVP);

     //               //std::cout << "CameraPos: "<<physicsComponent->position.x<<" "<<physicsComponent->position.y<<" "<< physicsComponent->position.z<<"\n";

     //           }
     //       }
        }
    }



    CameraSystem::CameraSystem(Shader* _shader)
    {
        Log::LogMessage("Constructor of CameraSystem Called");
        // EventSystem::registerEvent(EVENTS::KEY_PRESSED,this);
        shader = _shader;
        cam_x = 0;
        cam_y = 0;

        cam_x_velocity = 0.0f;
        cam_y_velocity = 0.0f;


    }

    int CameraSystem::PrintCamera(EventInfo* _eventInfo)
    {
        /*For now let's deliberatly check for key press, later well sophesticate this*/
        std::cout << "Camera Being handled\n";
        return 1;
    }

    int CameraSystem::handleEvent(EventInfo* _eventInfo)
    {
         std::cout<<"camera event boo"<<std::flush;
         
        if (_eventInfo->getEventTypeCode() == DREAM::KeyPressEvent::GetEventTypeCode() ) 
        {
            KeyPressEvent* keyPressEvent = dynamic_cast<KeyPressEvent*>(_eventInfo);
            
            if (keyPressEvent)
            {



                for (auto* tempEntity : entities)
                {
                    CameraEntity* tempCameraEntity = dynamic_cast<CameraEntity*>(tempEntity);

                    if (tempCameraEntity && tempCameraEntity->active)
                    {

                        PhysicsComponent* physicsComponent = tempCameraEntity->getComponent<PhysicsComponent>();

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
                            if(DREAM::KeyStates::KeyState[GLFW_KEY_LEFT_CONTROL].first == false)
                            physicsComponent->velocity = Vec4<float>(0, -40, 0, 0);
                            else
                                physicsComponent->velocity = Vec4<float>(0, 0, -1, 0);
                        }
                        if (DREAM::KeyStates::KeyState[GLFW_KEY_W].first == true)
                        {
                            // Move u
                            if(DREAM::KeyStates::KeyState[GLFW_KEY_LEFT_CONTROL].first == false)
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
                }

            }
        }
        else if (_eventInfo->getEventTypeCode() == DREAM::KeyReleaseEvent::GetEventTypeCode())
        {
            // std::cout<<"key removed boo"<<std::endl;
            DREAM::KeyReleaseEvent* tempKeyReleaseInfo = dynamic_cast<KeyReleaseEvent*>(_eventInfo);

            if (tempKeyReleaseInfo)
            {
                for (auto* tempEntity : entities)
                {
                    CameraEntity* tempCameraEntity = dynamic_cast<CameraEntity*>(tempEntity);

                    if (tempCameraEntity && tempCameraEntity->active)
                    {
                        PhysicsComponent* physicsComponent = tempCameraEntity->getComponent<PhysicsComponent>();
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
                }

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

        //delete _eventInfo;
        return 0;
    }
    Entity* CameraSystem::createDefaultCameraEntity()
    {
        Entity* defaultCameraEntity = new Entity();
		PhysicsComponent* physicsComponent = new PhysicsComponent(
			Vec4<float>(0, 0, 0, 0), // position
			Vec4<float>(0, 0, 0, 0), // velocity
			Vec4<float>(0, 0, 0, 0), // rotation
			Vec4<float>(0, 0, 0, 1)  // rotation_velocity
		);

        CameraComponent* cameraComponent = new CameraComponent(fov, aspect, near, far);

		MVPComponent* mvpComponent = new MVPComponent();
		defaultCameraEntity->addComponent(physicsComponent);
		defaultCameraEntity->addComponent(mvpComponent);

        return defaultCameraEntity;
    }
}