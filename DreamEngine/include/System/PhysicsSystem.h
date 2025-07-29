#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <ECS_Core/Core.hpp>
#include <functional>
#include <map>
#include "Vec3.hpp"

namespace DREAM{

	enum AXIS
	{
		X_AXIS,
		Y_AXIS,
		Z_AXIS
	};

class PhysicsSystem : public System
{
	const float*  dt_pointer; // delta time
public:

	//Constuctor
	PhysicsSystem(const float* _dt_pointer = nullptr) : dt_pointer(_dt_pointer) {
		Log::LogMessage("Physics System Constructor Called", LogLevel::INFO_LEVEL);
	}

	static Mat4<float> GetRotatioMatrixfromRotation( float _deltaRotation, AXIS _rotationAxis);
	static Vec4<float> GetEulerRotationfromRotationMatrix(const Mat4<float>& _rotationMatrix);
	void update() override;

};

}