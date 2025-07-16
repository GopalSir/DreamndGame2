#pragma once
#include <ECS_Core/Core.hpp>
#include "../Component/PhysicsComponent.hpp"
#include "../Component/MVPComponent.hpp"

class CameraEntity: public Entity
{

    public:
    /* Remember, entities will only hold data.  Let systems work on them.
    Now wer're reducing the main code, so camera entite will not be that dynamic. 
    We will force the initialization to have certain components attached*/
    // let's say 10 pixels per second
    bool active;
    CameraEntity(PhysicsComponent* _physicsComponent,MVPComponent* _mvpComponent);

    /*
    Camera is just for holding model view projection matrix. 
    Multiplying to cameras just adds their rotations, and then addds their trianslations and returns the MVP. 
    */

};