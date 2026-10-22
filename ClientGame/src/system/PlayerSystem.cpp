#include "../../include/system/PlayerSystem.hpp"

void PlayerSystem::update()
{
    for (auto entity : entities)
    {
        // Implement player-specific update logic here
        // For example, handle player input, 
        if(DREAM::KeyStates::KeyState[GLFW_KEY_W].first) // Check if 'W' key is pressed
        {
            DREAM::PhysicsComponent* physicsComponent = entity->getComponent<DREAM::PhysicsComponent>();
            if(physicsComponent)
            {
                physicsComponent->force = Vec4<float>(100.0f, 0.0f, 0.0f, 0.0f); 
            }
        }
    }   
}

void PlayerSystem::onEntityAddition(Entity* _entity)
{
    // This function is called when an entity is added to the PlayerSystem.
    // You can perform any initialization or setup for the entity here.
    // For example, you might want to check if the entity has a PhysicsComponent
    // and set some initial values or states.
    std::cout<<"Entity added to PlayerSystem with ID: " << _entity->getEntity() << std::endl;
}