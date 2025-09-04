#pragma once
#include <ECS_Core/Component.hpp>
#include <Component/PhysicsComponent.hpp>
#include <IEventHandler.hpp>
#include <Vec3.hpp>


namespace DREAM
{
	class CameraComponent : public Component
	{
	public:
		float fov;
		float aspect_ratio;
		float near;
		float far;
		bool active;
		
		Mat4<float> cameraWorldTransform; //homogenous rotation plus translation of the camera in world space
		Mat4<float> cameraViewMatrix;
		Mat4<float> projection;
		//Mat4<float> rx, ry, rz;
		//Mat4<float> position;

		//Mat4<float> mvp;


		CameraComponent(float fov, float aspect,float  near, float far) ;
		void doPostConstruct() override;
	};
}

