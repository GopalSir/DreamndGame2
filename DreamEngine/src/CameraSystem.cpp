#include "../include/System/CameraSystem.hpp"
namespace DREAM
{




    /*
	* Camera System is responsible for managing camera entities in the ECS.
    * The update function will go through all the registered entities and 
    * use the information available in camera componenet to generate 
    * View Matrix
    * Projection Matrix
	* because both these depend on the camera's position and rotation,
	* but camera's position and rotation are stored in the physics component, it's not intrinsic to the camera
    * 
    */

    CameraComponent* CameraSystem::getActiveCamera()
    {
		// Iterate over all entities managed by the system
		for (auto* tempEntity : entities)
		{
			CameraComponent* cameraComponent = tempEntity->getComponent<CameraComponent>();
			if (cameraComponent && cameraComponent->active)
			{
				Log::LogMessage("Active Camera Found", LogLevel::INFO_LEVEL);
                return cameraComponent;
			}
		}
		Log::LogMessage("No Active Camera Found", LogLevel::ERROR_LEVEL);
        return nullptr;
    }


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
				cameraComponent->cameraWorldTransform = calculateCameraWorldTransform(tempEntity->getComponent<PhysicsComponent>());
				// Calculates the view matrix based on the camera's position and rotation
                
                cameraComponent->cameraViewMatrix = calculateCameraViewMatrix(cameraComponent->cameraWorldTransform);

				// Invert the camera's rotation matrix to get the inverse transformation
				//cameraComponent->mvp = cameraTransformInverse(cameraComponent->getMVP());

                cameraComponent->projection =  CalculateProjectionMatrix(cameraComponent->fov,cameraComponent->aspect_ratio,cameraComponent->far,cameraComponent->near);
                


                
                PhysicsComponent* physicsComponent = tempEntity->getComponent<PhysicsComponent>();

                if (cameraComponent && physicsComponent)
                {
                    // Get the PhysicsComponent of the CameraEntity



                        // Update the position using the velocity
                    physicsComponent->position.x += physicsComponent->velocity.x;
                    physicsComponent->position.y += physicsComponent->velocity.y;
                    physicsComponent->position.z += physicsComponent->velocity.z;
                    physicsComponent->position.w = 1; // Usually w remains unchanged

                    physicsComponent->rotation.x += physicsComponent->rotation_velocity.x;
                    physicsComponent->rotation.y += physicsComponent->rotation_velocity.y;
                    physicsComponent->rotation.z += physicsComponent->rotation_velocity.z;
                    physicsComponent->rotation.w -= 0;




                    


                }
            }
            


            // Check if the entity is a CameraEntity and is active
			
        }
    }

    Mat4<float> CameraSystem::CalculateProjectionMatrix(float fov, float aspect, float far, float near)
    {
        float f = 1.0f / tan(fov / 2.0f);
        Mat4<float> proj;
        proj.r1 = Vec4<float>(f / aspect, 0, 0, 0);
        proj.r2 = Vec4<float>(0, f, 0, 0);
        proj.r3 = Vec4<float>(0, 0, (far + near) / (near - far), (2 * far * near) / (near - far));
        proj.r4 = Vec4<float>(0, 0, -1, 0);
        return proj;
    }

    CameraSystem::CameraSystem(Shader* _shader)
    {
        Log::LogMessage("Constructor of CameraSystem Called");
        // EventSystem::registerEvent(EVENTS::KEY_PRESSED,this);
        shader = _shader;
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
			Vec4<float>(0, 0, 100, 0), // velocity
			Vec4<float>(0, 0, 0, 0), // rotation
			Vec4<float>(0, 0, 0, 1)  // rotation_velocity
		);

               float fov = 45.0f * (3.1415926f / 180.0f);

               int windowWidth, windowHeight;
               GLFWwindow* currentWindow = glfwGetCurrentContext();
               glfwGetFramebufferSize(currentWindow, &windowWidth, &windowHeight);

               float aspect = (float)windowWidth / windowHeight;
               float near = 0.1f;
               float far =1000.0f;

        CameraComponent* cameraComponent = new CameraComponent(fov, aspect, near, far);
		cameraComponent->active = true; // Set the camera as active
		
		defaultCameraEntity->addComponent(physicsComponent);
		defaultCameraEntity->addComponent(cameraComponent);

        return defaultCameraEntity;
    }

    Mat4<float> CameraSystem::calculateCameraWorldTransform(const PhysicsComponent* _physicsComponent)
    {
        /*
		We'll set the cameraWorldTransform to the following matrix, using the rotation and translation from physics Component
		[R  T]
		[0  1]
		where R is the rotation matrix and T is the translation vector.
        */

		float _x = _physicsComponent->rotation.x;
		float _y = _physicsComponent->rotation.y;
		float _z = _physicsComponent->rotation.z;

        Mat4<float> rz = Mat4<float>(
            Vec4<float>(cos(_z), -sin(_z), 0, 0),
            Vec4<float>(sin(_z), cos(_z), 0, 0),
            Vec4<float>(0, 0, 1, 0),
            Vec4<float>(0, 0, 0, 1)

        );

        Mat4<float> ry = Mat4<float>(
            Vec4<float>(cos(_y), 0, sin(_y), 0),
            Vec4<float>(0, 1, 0, 0),
            Vec4<float>(-sin(_y), 0, cos(_y), 0),
            Vec4<float>(0, 0, 0, 1)

        );

        Mat4<float> rx = Mat4<float>(
            Vec4<float>(1, 0, 0, 0),
            Vec4<float>(0, cos(_x), -sin(_x), 0),
            Vec4<float>(0, sin(_x), cos(_x), 0),
            Vec4<float>(0, 0, 0, 1)

        );

		// Combine the rotation matrices by multiplying and then finally change 'w' component to translation 
		Mat4<float> rotationMatrix = rz * ry * rx;
        Mat4<float> result = rotationMatrix;
		result.r1.w = _physicsComponent->position.x;
		result.r2.w = _physicsComponent->position.y;
		result.r3.w = _physicsComponent->position.z;
		result.r4 = Vec4<float>(0, 0, 0, 1); // Last row is always [0, 0, 0, 1] for homogeneous coordinates
		return result;


    }

	Mat4<float> CameraSystem::calculateCameraViewMatrix(const Mat4<float>& _cameraWorldTransform) {
		/*
		The view matrix is the inverse of the camera's world transform.
		It transforms points from world space to camera space.
		*/
        //first we'll transpose the 3*3 part to get the inverse of the rotation matrix
        Mat3<float> rotationMatrix3x3Inverse(
            Vec3<float>(_cameraWorldTransform.r1.x, _cameraWorldTransform.r2.x, _cameraWorldTransform.r3.x),
            Vec3<float>(_cameraWorldTransform.r1.y, _cameraWorldTransform.r2.y, _cameraWorldTransform.r3.y),
            Vec3<float>(_cameraWorldTransform.r1.z, _cameraWorldTransform.r2.z, _cameraWorldTransform.r3.z)
        );

        //Now the translation component is also added. It's value is -R * T
        Vec3<float> translation(
            Vec3<float>::dot(-rotationMatrix3x3Inverse.r1, Vec3<float>(_cameraWorldTransform.r1.w, _cameraWorldTransform.r2.w, _cameraWorldTransform.r3.w)),
            Vec3<float>::dot(-rotationMatrix3x3Inverse.r2, Vec3<float>(_cameraWorldTransform.r1.w, _cameraWorldTransform.r2.w, _cameraWorldTransform.r3.w)),
            Vec3<float>::dot(-rotationMatrix3x3Inverse.r3, Vec3<float>(_cameraWorldTransform.r1.w, _cameraWorldTransform.r2.w, _cameraWorldTransform.r3.w))
        );

        Mat4<float> result(rotationMatrix3x3Inverse, translation);


        //The complete inverse rotation matrix is then constructed by [rotationMatrix3x3 inverse, -rotationMatrix3x3 inverse *translation vector
        //                                                                      0                ,               1                ]
        // Now we combine the 3*3 rotation matrix with the translation vector
        return result;
		
	}

}