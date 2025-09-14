#pragma once
#include <ECS_Core/Core.hpp>
#include <Component/PositionComponent.hpp>
#include <System/RenderSystem.hpp>
#include <Component/CameraComponent.h>
#include <IEventHandler.hpp>
#include <KeyStates.h>

class CrappyBirdComponent :
    public Component, public DREAM::IEventHandler
{
public:
    int score;

    //Position of bird when last pillar was generated
    PositionComponent<float> p_previous;
    DREAM::RenderSystem* renderSystem;
    PhysicsComponent* cameraPhysicsComponent;
    PhysicsComponent* birdPhysicsComponent;
    bool* gameState;

    float r_limit;


    CrappyBirdComponent() {
        p_previous = PositionComponent<float>(0, 0, 0);
        score = 0;
        r_limit = 200;
        renderSystem = nullptr;
    }

    int handleEvent(DREAM::EventInfo* _eventInfo) override;
    
    

};

