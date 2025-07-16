#pragma once
#include <ECS_Core/Core.hpp>
#include "../Vec3.hpp"
#include <cmath>

class MVPComponent: public Component
{
	Mat4<float> perspective;
    Mat4<float> rx,ry,rz;
    Mat4<float> position;

    Mat4<float> mvp;

    public: 
    
    
    MVPComponent();
    void setRotation(float _x,float _y, float _z);
    void setRotation(Mat4<float> _roation);

    void setPosition(float _x,float _y, float _z);
    void setPosition(Vec4<float>);

	static Mat4<float> CreatePerspective(float fov, float aspect, float near, float far);
    void setPerspective(Mat4<float> _perspective);

    Mat4<float> getPerspective();

    Mat4<float> getMVP();

    MVPComponent& operator* (const MVPComponent& _other ) const;
    

};