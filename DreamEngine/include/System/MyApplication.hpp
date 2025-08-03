#pragma once
#include <ECS_Core/Core.hpp>
#include "../Entity/CameraEntity.hpp"
#include "../Entity/TriangleEntity.hpp"
#include "../Entity/RectangleEntity.hpp"
#include "../Component/PositionComponent.hpp"
#include "../Component/VerticesComponent.hpp"
#include "../Component/RotationComponent.hpp"
#include "../Component/WindowComponent.hpp"
#include "../Component/VertexAttribComponent.hpp"
#include "../Component/DrawableComponent.hpp"
#include "../Component/PhysicsComponent.hpp"
#include "CameraSystem.hpp"
#include "RenderSystem.hpp"
#include "EventSystem.hpp"
#include "PhysicsSystem.h"
#include "../glfwKeyCallBacks.hpp"
#include "../VertexAttribPointerGenerator.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include "../Shader.hpp"

namespace DREAM {

    class MyApplication
    {
        GLFWwindow* glfwWindow;
        CameraEntity* cameraEntity;
        Log log;
        CameraSystem* cameraSystem;
        RenderSystem* renderSystem;
		PhysicsSystem* physicsSystem;

        std::vector<System*> gameSystems;
        bool gamestate;
        Shader* programShader;


        int gameFPS;
        std::chrono::time_point<std::chrono::high_resolution_clock> frameStart;
        std::chrono::nanoseconds actualFrameTime;
        std::chrono::nanoseconds requiredFrameTime;
        std::chrono::nanoseconds requiredSleepTime;
		float deltaTime;

        std::chrono::nanoseconds calculateRequiredFrameTime(int _gameFPS);
        int playerEntityID, enemyEntityID;
        void bridgeSystems();
        void completePostConstruct();

    public:
        MyApplication();
        ~MyApplication();

        void run();


        //Methods exposed to cliend side implementation 
        RenderSystem* GetRenderSystem();
		CameraSystem* GetCameraSystem();
        //EventSystem* GetEventSystem();

        void updateSystems();
        bool getGameState();
        void setGameState(bool _gameState);
        void setTriangleEntity();
        bool initializeShaders();
        void     setUpCameraSystem();
        void setupGizmo();
		void gizmoVisibility(bool _visibility);

    };
}