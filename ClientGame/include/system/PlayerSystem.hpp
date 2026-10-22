#include <ECS_Core/System.hpp>
#include <Component/PhysicsComponent.hpp>
#include <IEventHandler.hpp>
#include <KeyStates.h>

class PlayerSystem: public System
{
    public:
    void update() override;
    void onEntityAddition(Entity*) override;
    
};