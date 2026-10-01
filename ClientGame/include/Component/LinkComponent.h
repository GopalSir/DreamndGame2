#pragma once

#include <ECS_Core/Core.hpp>
#include <Component/JointComponent.h>

enum LINK_SHAPE
{
    SQUARE,
    SPHERE,
    CYLINDER
};

class LinkComponent : public Component
{
public:
    //Now I decide what kinda links are allowed and wether I should care about it here, or let some other code deals with shape of link
    
    //Next and prev joint. 
    Component* prev_joint;
    Component* next_joint;

    //Link Shape type
    LINK_SHAPE link_shape;

    
};