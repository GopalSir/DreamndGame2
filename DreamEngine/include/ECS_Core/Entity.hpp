#pragma once
#include <typeindex>
#include <vector>

class Component;

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
    virtual ~Entity(){};
};


