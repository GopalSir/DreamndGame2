#pragma once
#include <ECS_Core/Core.hpp>
#include "../Entity/CameraEntity.hpp"
#include "../IEventHandler.hpp"
#include "../Component/VerticesComponent.hpp"
#include "../Component/VertexAttribComponent.hpp"
#include "../Component/DrawableComponent.hpp"
#include "../glheaders.hpp"

namespace DREAM
{
    class RenderSystem :public System, public IEventHandler
    {
    public:
        void update() override;
        int handleEvent(EventInfo* _eventInfo) override;
        RenderSystem(GLFWwindow* _glfwWindow);
        bool initEntityBuffers(int _index);


    };

}