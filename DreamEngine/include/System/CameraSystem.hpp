#pragma once
#include <ECS_Core/Core.hpp>
#include <math.h>
#include "../Vec3.hpp"
#include "../EVENTS.hpp"
#include "../System/EventSystem.hpp"
#include "../System/PhysicsSystem.h"
//#include "../Entity/CameraEntity.hpp"
#include "../Component/CameraComponent.h"
#include "../IEventHandler.hpp"
#include "../Shader.hpp"
#include "../KeyStates.h"

namespace DREAM {
    class CameraSystem :public System, public IEventHandler
    {
        Shader* shader;
        void updateCameraPosition(PhysicsComponent* _physicsComponent);
		void updateCameraRotation(PhysicsComponent* _physicsComponent, CameraComponent* _cameraComponent);
    public:
		const float* dt_pointer; // delta time
        CameraSystem(Shader* _shader, const float* _dt_pointer);
        void update() override;

        int PrintCamera(EventInfo* _eventInfo);
        int handleEvent(EventInfo* _eventInfo) override;
		static Entity* createDefaultCameraEntity();
        Mat4<float> CalculateProjectionMatrix(float fov, float aspect, float far, float near);
        Mat4<float> calculateCameraWorldTransform(const PhysicsComponent* _physicsComponent, CameraComponent* _cameraComponent);
		Mat4<float> calculateCameraViewMatrix(const Mat4<float>& _cameraWorldTransform);
        CameraComponent* getActiveCamera();

    };

}