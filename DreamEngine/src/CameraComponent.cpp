#include "Component/CameraComponent.h"

namespace DREAM
{
    CameraComponent::CameraComponent(float fov, float aspect, float far , float near)
    {
		this->fov = fov;
		this->aspect_ratio = aspect;
		this->near = near;
		this->far = far;
		perspective = CreatePerspective(fov, aspect, far, near);
		mvp = Mat4<float>(Vec4<float>(1, 0, 0, 0),
			Vec4<float>(0, 1, 0, 0),
			Vec4<float>(0, 0, 1, 0),
			Vec4<float>(0, 0, 0, 1));
		setRotation(0, 0, 0); // Initialize rotation to identity
    }
    void CameraComponent::setRotation(float _x, float _y, float _z)
    {
        rz = Mat4<float>(
            Vec4<float>(cos(_z), -sin(_z), 0, 0),
            Vec4<float>(sin(_z), cos(_z), 0, 0),
            Vec4<float>(0, 0, 1, 0),
            Vec4<float>(0, 0, 0, 1)

        );

        ry = Mat4<float>(
            Vec4<float>(cos(_y), 0, sin(_y), 0),
            Vec4<float>(0, 1, 0, 0),
            Vec4<float>(-sin(_y), 0, cos(_y), 0),
            Vec4<float>(0, 0, 0, 1)

        );

        rx = Mat4<float>(
            Vec4<float>(1, 0, 0, 0),
            Vec4<float>(0, cos(_x), -sin(_x), 0),
            Vec4<float>(0, sin(_x), cos(_x), 0),
            Vec4<float>(0, 0, 0, 1)

        );


        mvp = rz * ry * rx;

    }

    void CameraComponent::setPosition(float _x, float _y, float _z)
    {
        mvp.r1.w = _x;
        mvp.r2.w = _y;
        mvp.r3.w = _z;


    }

    void CameraComponent::setRotation(Mat4<float> _rotation)
    {
        mvp = _rotation;
    }

    Mat4<float> CameraComponent::CreatePerspective(float fov, float aspect, float far, float near)
    {
        float f = 1.0f / tan(fov / 2.0f);
        Mat4<float> proj;
        proj.r1 = Vec4<float>(f / aspect, 0, 0, 0);
        proj.r2 = Vec4<float>(0, f, 0, 0);
        proj.r3 = Vec4<float>(0, 0, (far + near) / (near - far), (2 * far * near) / (near - far));
        proj.r4 = Vec4<float>(0, 0, -1, 0);
        return proj;
    }

    void CameraComponent::setPerspective(Mat4<float> _perspective)
    {
        perspective = _perspective;

    }

    Mat4<float> CameraComponent::getPerspective()
    {
        return perspective;
    }

    Mat4<float> CameraComponent::getMVP()
    {
        return mvp;
    }
    void CameraComponent::calculateViewMatrix()
    {
       //View matrix depends on camera's rotaiton and position. We will calculate it using
       //the PhysicsComponent of the entity to which this CameraComponent is attached to. 

		PhysicsComponent* physicsComponent = this->entity->getComponent<PhysicsComponent>();
		if (physicsComponent)
		{
            setRotation(physicsComponent->rotation.x, physicsComponent->rotation.y, physicsComponent->rotation.z);
			setPosition(physicsComponent->position.x, physicsComponent->position.y, physicsComponent->position.z);
			
		}
		else
		{
			Log::LogMessage("PhysicsComponent not found in CameraComponent", LogLevel::ERROR_LEVEL);
		}
        
        



    }

	void CameraComponent::CalculateProjectionMatrix()
	{
		//Projection matrix is calculated using the perspective matrix
		perspective = CreatePerspective(fov, aspect_ratio, near, far);

	}

    void CameraComponent::CalculateMVP()
    {
        mvp =  perspective * mvp;
    }


   /* CameraComponent::CameraComponent()
    {
        rz = Mat4<float>(
            Vec4<float>(1, 0, 0, 0),
            Vec4<float>(0, 1, 0, 0),
            Vec4<float>(0, 0, 1, 0),
            Vec4<float>(0, 0, 0, 0)

        );

        ry = Mat4<float>(
            Vec4<float>(1, 0, 0, 0),
            Vec4<float>(0, 1, 0, 0),
            Vec4<float>(0, 0, 1, 0),
            Vec4<float>(0, 0, 0, 0)
        );

        rx = Mat4<float>(
            Vec4<float>(1, 0, 0, 0),
            Vec4<float>(0, 1, 0, 0),
            Vec4<float>(0, 0, 1, 0),
            Vec4<float>(0, 0, 0, 0));
    };*/

}


