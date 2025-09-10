#pragma once
#include <ECS_Core/Core.hpp>
#include <System/PhysicsSystem.h>
#include "../Entity/CameraEntity.hpp"
#include "../IEventHandler.hpp"
#include "../Component/VerticesComponent.hpp"
#include "../Component/VertexAttribComponent.hpp"
#include "../Component/DrawableComponent.hpp"
#include "../Component/CameraComponent.h"
#include "../Shader.hpp"
#include "../glheaders.hpp"
#include "../Vec3.hpp"

namespace DREAM
{
    class RenderSystem :public System, public IEventHandler
    {
    private:
        Shader* shader;
		GLFWwindow* glfwWindow;
        CameraComponent* activeCameraComponent;
    public:
        void update() override;
        int handleEvent(EventInfo* _eventInfo) override;
        RenderSystem(GLFWwindow* _glfwWindow, Shader* _shader );
        Mat4<float> CalculateMVP(Mat4<float>& _projection, Mat4<float>& _view, Mat4<float>& _model);
        bool initEntityBuffers(int _index);
		void SetActiveCamera(CameraComponent* _cameraComoponent) { activeCameraComponent = _cameraComoponent; };

        static Vec4<float> ScreenToWorldCoordinate(Vec4<float> _screenCoord, CameraComponent* _cameraComponent);
        static Vec4<float> ScreenToNDC(Vec4<float> _screenCoord);


    };

}