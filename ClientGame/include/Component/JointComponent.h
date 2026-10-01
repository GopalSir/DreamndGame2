#pragma once
#include <ECS_Core/Core.hpp>
#include <Vec3.hpp>

class LinkComponent;

/*
This is supposed to be an abstract class. 
*/
class JointComponent: public Component
{
    private:
    JointComponent();

    protected:
    //All joints will have these 2 peoperties at least, even if set to null
    //So putting it up as a base class
    LinkComponent* prev_link;
    LinkComponent* next_link;
};

class RevoluteJointComponent : public Component
{
public:
     // The axis of the joint
     Vec3<float> axis;

     //The rotation amount of the joint in degrees
     float rotation;


    
    
    RevoluteJointComponent();
    ~RevoluteJointComponent();

private:
    // Private members for joint properties
};

