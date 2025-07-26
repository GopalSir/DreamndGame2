#pragma once
#include <typeindex>
#include <vector>
#include <ECS_Core/Component.hpp>

class Entity
{
    int entityID;
    std::vector<Component*> components;

    public:
    int getEntity();

    template<typename T>
    T* getComponent()
    {
        for(auto* c : components)
        {
            if(std::type_index(typeid(T))==std::type_index(typeid(*c)))
            {
                return static_cast<T*>(c);
            }
        }
        return nullptr;
    }

    void addComponent(Component* _component);
    void doPostConstruct() {
		for (auto* component : components) {
			component->doPostConstruct();
		}
    }
    virtual ~Entity(){};
};


