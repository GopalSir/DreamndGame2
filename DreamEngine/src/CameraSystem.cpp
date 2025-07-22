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


                CameraComponent* tempCameraComponent = tempEntity->getComponent<CameraComponent>();
                PhysicsComponent* physicsComponent = tempEntity->getComponent<PhysicsComponent>();

                if (tempCameraComponent && physicsComponent)
                {
                    // Get the PhysicsComponent of the CameraEntity



                        // Update the position using the velocity
                    physicsComponent->position.x -= physicsComponent->velocity.x;
                    physicsComponent->position.y -= physicsComponent->velocity.y;
                    physicsComponent->position.z -= physicsComponent->velocity.z;
                    physicsComponent->position.w = 1; // Usually w remains unchanged

                    physicsComponent->rotation.x -= physicsComponent->rotation_velocity.x;
                    physicsComponent->rotation.y -= physicsComponent->rotation_velocity.y;
                    physicsComponent->rotation.z -= physicsComponent->rotation_velocity.z;
                    physicsComponent->rotation.w -= 0;



                    Mat4<float> tempMVP = tempCameraComponent->getMVP();

                    //Logging MVP
                    std::cout << tempMVP.r1.x << " " << tempMVP.r1.y << " " << tempMVP.r1.z << " " << tempMVP.r1.w << "\n";
                    std::cout << tempMVP.r2.x << " " << tempMVP.r2.y << " " << tempMVP.r2.z << " " << tempMVP.r2.w << "\n";
                    std::cout << tempMVP.r3.x << " " << tempMVP.r3.y << " " << tempMVP.r3.z << " " << tempMVP.r3.w << "\n";
                    std::cout << tempMVP.r4.x << " " << tempMVP.r4.y << " " << tempMVP.r4.z << " " << tempMVP.r4.w << "\n";
                    /*std::cout << mvpComponent->getPerspective().r1.x << " " << mvpComponent->getPerspective().r1.y << " " << mvpComponent->getPerspective().r1.z << " " << mvpComponent->getPerspective().r1.w << "\n";
                    std::cout << mvpComponent->getPerspective().r2.x << " " << mvpComponent->getPerspective().r2.y << " " << mvpComponent->getPerspective().r2.z << " " << mvpComponent->getPerspective().r2.w << "\n";
                    std::cout << mvpComponent->getPerspective().r3.x << " " << mvpComponent->getPerspective().r3.y << " " << mvpComponent->getPerspective().r3.z << " " << mvpComponent->getPerspective().r3.w << "\n";
                    std::cout << mvpComponent->getPerspective().r4.x << " " << mvpComponent->getPerspective().r4.y << " " << mvpComponent->getPerspective().r4.z << " " << mvpComponent->getPerspective().r4.w << "\n";*/

                    shader->setUniform("mvp", tempMVP);

                    //std::cout << "CameraPos: "<<physicsComponent->position.x<<" "<<physicsComponent->position.y<<" "<< physicsComponent->position.z<<"\n";


                }
            }
            


            // Check if the entity is a CameraEntity and is active
			
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
         
        

        //delete _eventInfo;
        return 0;
    }
    Entity* CameraSystem::createDefaultCameraEntity()
    {
        Entity* defaultCameraEntity = new Entity();
		PhysicsComponent* physicsComponent = new PhysicsComponent(
			Vec4<float>(0, 0, 0, 0), // position
			Vec4<float>(0, 0, -100, 0), // velocity
			Vec4<float>(0, 0, 0, 0), // rotation
			Vec4<float>(0, 0, 0, 1)  // rotation_velocity
		);

               float fov = 45.0f * (3.1415926f / 180.0f);

               int windowWidth, windowHeight;
               GLFWwindow* currentWindow = glfwGetCurrentContext();
               glfwGetFramebufferSize(currentWindow, &windowWidth, &windowHeight);

               float aspect = (float)windowWidth / windowHeight;
               float near = 0.1f;
               float far =300.0f;

        CameraComponent* cameraComponent = new CameraComponent(fov, aspect, near, far);

		
		defaultCameraEntity->addComponent(physicsComponent);
		defaultCameraEntity->addComponent(cameraComponent);

        return defaultCameraEntity;
    }
}