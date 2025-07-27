#include "../System/PhysicsSystem.h"

namespace DREAM{
    //This function expects a delta rotation in degrees. 
Mat4<float> DREAM::PhysicsSystem::GetRotatioMatrixfromRotation( float _deltaRotation, AXIS _rotationAxis)
{
	Mat4<float> result;
    
	_deltaRotation = _deltaRotation * (3.14159265358979323846 / 180.0); // Convert degrees to radians

	if (_rotationAxis == AXIS::X_AXIS)
	{
        result = Mat4<float>(
            Vec4<float>(1, 0, 0, 0),
            Vec4<float>(0, cos(_deltaRotation), -sin(_deltaRotation), 0),
            Vec4<float>(0, sin(_deltaRotation), cos(_deltaRotation), 0),
            Vec4<float>(0, 0, 0, 1));
	}
	else if (_rotationAxis == AXIS::Y_AXIS)
	{
        result = Mat4<float>(
            Vec4<float>(cos(_deltaRotation), 0, sin(_deltaRotation), 0),
            Vec4<float>(0, 1, 0, 0),
            Vec4<float>(-sin(_deltaRotation), 0, cos(_deltaRotation), 0),
            Vec4<float>(0, 0, 0, 1));
	}
	else if (_rotationAxis == AXIS::Z_AXIS)
	{
        result = Mat4<float>(
            Vec4<float>(cos(_deltaRotation), -sin(_deltaRotation), 0, 0),
            Vec4<float>(sin(_deltaRotation), cos(_deltaRotation), 0, 0),
            Vec4<float>(0, 0, 1, 0),
            Vec4<float>(0, 0, 0, 1));
	}
    return result;
}

void PhysicsSystem::update()
{
    //for (auto* tempEntity : entities)
    //{
    //    //We will update the position based on velocity and rotation based on rotation (local rotation) 

    //}
}


}