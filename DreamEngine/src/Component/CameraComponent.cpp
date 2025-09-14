#include "Component/CameraComponent.h"

namespace DREAM
{
    CameraComponent::CameraComponent(float fov, float aspect, float near, float far)
    {
        this->fov = fov;
        this->aspect_ratio = aspect;
        this->near = near;
        this->far = far;
        this->active = true;
		this->cameraWorldTransform = Mat4<float>::identity; // Initialize to identity matrix
    }

    void CameraComponent::doPostConstruct()
    {

    }

}


