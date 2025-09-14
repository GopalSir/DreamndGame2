#include "../../include/Component/CrappyBirdComponent.h"

int CrappyBirdComponent::handleEvent(DREAM::EventInfo* _eventInfo)
{
    
    if (_eventInfo->getEventTypeCode() == DREAM::KeyPressEvent::GetEventTypeCode())
    {
        if (DREAM::KeyStates::KeyState[GLFW_KEY_SPACE].first == true)
        {
            //birdPhysicsComponent->position.y += 130;
            if (birdPhysicsComponent->velocity.y < 0)
            {
                birdPhysicsComponent->velocity.y = -birdPhysicsComponent->velocity.y;
            }
            else 
            {
                birdPhysicsComponent->velocity.y += 20;
            }
            //birdPhysicsComponent->rotation = Vec4<float>(0, 0, 0,0);
       }
   }

    return 0;
}
