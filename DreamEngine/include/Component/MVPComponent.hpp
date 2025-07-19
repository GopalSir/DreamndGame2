#pragma once
#include <ECS_Core/Core.hpp>
#include "../Vec3.hpp"
#include <cmath>

class MVPComponent: public Component
{

    public: 
    
    
    MVPComponent();

    void setPosition(Vec4<float>);



    MVPComponent& operator* (const MVPComponent& _other ) const;
    

};