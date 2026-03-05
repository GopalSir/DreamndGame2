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
        //std::cout << *dt_pointer << std::endl;
        // Iterate over all entities managed by the system
        for (auto* tempEntity : entities)
        {

            //We'll only update view matrices here. 
            CameraComponent* cameraComponent = tempEntity->getComponent<CameraComponent>();
            PhysicsComponent* physicsComponent = tempEntity->getComponent<PhysicsComponent>();

            


                if (cameraComponent && physicsComponent)
                {
                    // Get the PhysicsComponent of the CameraEntity



					// Update the position using the velocity    
					updateCameraPosition(physicsComponent);

					// Update the rotation using the rotation matrix
					//updateCameraRotation(physicsComponent, cameraComponent);


                    cameraComponent->cameraWorldTransform = calculateCameraWorldTransform(physicsComponent,cameraComponent);
                    // Calculates the view matrix based on the camera's position and rotation

                    cameraComponent->cameraViewMatrix = calculateCameraViewMatrix(cameraComponent->cameraWorldTransform);

                    // Invert the camera's rotation matrix to get the inverse transformation
                    //cameraComponent->mvp = cameraTransformInverse(cameraComponent->getMVP());

                    cameraComponent->projection = CalculateProjectionMatrix(cameraComponent->fov, cameraComponent->aspect_ratio, cameraComponent->far, cameraComponent->near);
				}
				else
				{
					Log::LogMessage("CameraComponent or PhysicsComponent is null in CameraSystem update", LogLevel::ERROR_LEVEL);

                }
            
            


            // Check if the entity is a CameraEntity and is active
			
        }
    }

    Mat4<float> CameraSystem::CalculateProjectionMatrix(float fov, float aspect, float far, float near)
    {
        float f = 1.0f / tan(fov / 2.0f);
        Mat4<float> proj;
        proj.r1 = Vec4<float>(f / aspect, 0, 0, 0);
        proj.r2 = Vec4<float>(0, f, 0, 0 );
        proj.r3 = Vec4<float>(0, 0, (far + near) / (near - far), (2 * far * near) / (near - far));

        //proj.r3 = Vec4<float>(0, 0, (far + near) / (near - far), (2 * far * near) / (near - far));
        proj.r4 = Vec4<float>(0, 0, -1, 0);
        return proj;
    }

    void CameraSystem::updateCameraPosition(PhysicsComponent* _physicsComponent)
    {
		_physicsComponent->position = _physicsComponent->position +  (_physicsComponent->velocity * (*dt_pointer));
    }

    void CameraSystem::updateCameraRotation(PhysicsComponent* _physicsComponent, CameraComponent* _cameraComponent)
    {
  //      //Need to extract back the rotation of the camera using it's world transform matrix
		//Mat4<float> cameraWorldTransform = _cameraComponent->cameraWorldTransform;

		//Vec4<float> new_euler_rotation = PhysicsSystem::GetEulerRotationfromRotationMatrix(cameraWorldTransform);

		// Update the rotation of the physics component based on the new euler rotation
	/*	_physicsComponent->rotation.x = new_euler_rotation.x;
		_physicsComponent->rotation.y = new_euler_rotation.y;
		_physicsComponent->rotation.z = new_euler_rotation.z;*/




    }
    CameraSystem::CameraSystem(Shader* _shader, const float* _dt_pointer)
    {
        Log::LogMessage("Constructor of CameraSystem Called");
        // EventSystem::registerEvent(EVENTS::KEY_PRESSED,this);
        shader = _shader;
		dt_pointer = _dt_pointer; // Store the pointer to delta time
    }

    int CameraSystem::PrintCamera(EventInfo* _eventInfo)
    {
        /*For now let's deliberatly check for key press, later well sophesticate this*/
        std::cout << "Camera Being handled\n";
        return 1;
    }

    int CameraSystem::handleEvent(EventInfo* _eventInfo)
    {
         //std::cout<<"camera event boo"<<std::flush;
         
        

        //delete _eventInfo;
        return 0;
    }
    Entity* CameraSystem::createDefaultCameraEntity()
    {
        Entity* defaultCameraEntity = new Entity();
		PhysicsComponent* physicsComponent = new PhysicsComponent(
			Vec4<float>(0, 0, 0, 0), // velocity
			Vec4<float>(0, 0, 100, 1), // position
			Vec4<float>(0, 0, 0, 0), // rotation
			Vec4<float>(0, 0, 0, 0)  // rotation_velocity
		);

               float fov = 60.0f * (3.1415926f / 180.0f);

               int windowWidth, windowHeight;
               GLFWwindow* currentWindow = glfwGetCurrentContext();
               glfwGetFramebufferSize(currentWindow, &windowWidth, &windowHeight);

               float aspect = (float)windowWidth / windowHeight;
               float near = 0.3f;
               float far =1000.0f;

        CameraComponent* cameraComponent = new CameraComponent(fov, aspect, near, far);
		cameraComponent->active = true; // Set the camera as active
		
		defaultCameraEntity->addComponent(physicsComponent);
		defaultCameraEntity->addComponent(cameraComponent);

        return defaultCameraEntity;
    }

    Mat4<float> CameraSystem::calculateCameraWorldTransform(const PhysicsComponent* _physicsComponent, CameraComponent* _cameraComponent)
    {
    

		float local_rotation_x = _physicsComponent->rotation_velocity.x * (*dt_pointer);
		float local_rotation_y = _physicsComponent->rotation_velocity.y * (*dt_pointer);
		float local_rotation_z = _physicsComponent->rotation_velocity.z * (*dt_pointer);

		Mat4<float> deltaRotationMatrix_x = PhysicsSystem::GetRotatioMatrixfromRotation(local_rotation_x, AXIS::X_AXIS );
		Mat4<float> deltaRotationMatrix_y = PhysicsSystem::GetRotatioMatrixfromRotation(local_rotation_y, AXIS::Y_AXIS);
		Mat4<float> deltaRotationMatrix_z = PhysicsSystem::GetRotatioMatrixfromRotation(local_rotation_z, AXIS::Z_AXIS);

		// Combine the delta rotation matrices
		Mat4<float> deltaRotationMatrix = deltaRotationMatrix_z * deltaRotationMatrix_y * deltaRotationMatrix_x;


       /* Mat4<float> result = PhysicsSystem::GetRotatioMatrixfromRotation(_physicsComponent->rotation.z, AXIS::Z_AXIS) * PhysicsSystem::GetRotatioMatrixfromRotation(_physicsComponent->rotation.y, AXIS::Y_AXIS) * PhysicsSystem::GetRotatioMatrixfromRotation(_physicsComponent->rotation.x, AXIS::X_AXIS); */
        Mat4<float> result = _cameraComponent->cameraWorldTransform;
		// Now we combine the rotation matrix with the translation vector3
		// The translation vector is the position of the camera in world space
		result = result * deltaRotationMatrix; // Apply delta rotation to the camera's world transform
		
		//Finally set the positition of the camera to the physics component's position 
		result.r1.w = _physicsComponent->position.x;
		result.r2.w = _physicsComponent->position.y;
		result.r3.w = _physicsComponent->position.z;
		// The w component of the translation vector is set to 1 for homogeneous coordinates
		result.r4 = Vec4<float>(0, 0, 0, 1); // Last row for homogeneous coordinates

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