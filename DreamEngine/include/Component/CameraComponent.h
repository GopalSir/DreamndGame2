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

		Mat4<float> perspective;
		Mat4<float> rx, ry, rz;
		Mat4<float> position;

		Mat4<float> mvp;


		CameraComponent() = default;
	
		void setRotation(float _x, float _y, float _z);
		void setRotation(Mat4<float> _roation);

		void setPosition(float _x, float _y, float _z);

		static Mat4<float> CreatePerspective(float fov, float aspect, float near, float far);
		void setPerspective(Mat4<float> _perspective);

		Mat4<float> getPerspective();

		Mat4<float> getMVP();
		void calculateViewMatrix();
		void CalculateProjectionMatrix();
		void CalculateMVP() ;
	};
}

