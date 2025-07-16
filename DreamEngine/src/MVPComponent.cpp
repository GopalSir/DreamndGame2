#include "../include/Component/MVPComponent.hpp"

void MVPComponent::setRotation(float _x, float _y, float _z)
{
    rz = Mat4<float>(
        Vec4<float>(cos(_z),-sin(_z),0,0),
        Vec4<float>(sin(_z),cos(_z),0,0),
        Vec4<float>(0,0,1,0),
        Vec4<float>(0,0,0,1)
        
    );

    ry = Mat4<float> (
        Vec4<float>(cos(_y),0,sin(_y),0),
        Vec4<float>(0,1,0,0),
        Vec4<float>(-sin(_y),0,cos(_y),0),
        Vec4<float>(0,0,0,1)
        
    );

    rx = Mat4<float>(
        Vec4<float>(1,0,0,0),
        Vec4<float>(0,cos(_x),-sin(_x),0),
        Vec4<float>(0,sin(_x),cos(_x),0),
        Vec4<float>(0,0,0,1)
        
    );


    mvp = rz*ry*rx;
    
}

void MVPComponent::setPosition(float _x,float _y, float _z)
{
    mvp.r1.w = _x;
    mvp.r2.w = _y;
    mvp.r3.w = _z;
    

}

void MVPComponent::setRotation(Mat4<float> _rotation)
{
    mvp = _rotation;
}

Mat4<float> MVPComponent::CreatePerspective(float fov, float aspect, float far , float near)
{
    float f = 1.0f / tan(fov / 2.0f);
    Mat4<float> proj;
    proj.r1 = Vec4<float>(f / aspect, 0, 0, 0);
    proj.r2 = Vec4<float>(0, f, 0, 0);
    proj.r3 = Vec4<float>(0, 0, (far + near) / (near - far), (2 * far * near) / (near - far));
    proj.r4 = Vec4<float>(0, 0, -1, 0);
    return proj;
}

void MVPComponent::setPerspective(Mat4<float> _perspective)
{
	perspective = _perspective;
	 
}

Mat4<float> MVPComponent::getPerspective()
{
	return perspective;
}

Mat4<float> MVPComponent::getMVP()
{
    return perspective*mvp;
};

MVPComponent::MVPComponent()
{
    rz = Mat4<float>(
        Vec4<float>(1,0,0,0),
        Vec4<float>(0,1,0,0),
        Vec4<float>(0,0,1,0),
        Vec4<float>(0,0,0,0)
        
    );

    ry =  Mat4<float>(
        Vec4<float>(1,0,0,0),
        Vec4<float>(0,1,0,0),
        Vec4<float>(0,0,1,0),
        Vec4<float>(0,0,0,0)
    );

    rx =  Mat4<float>(
        Vec4<float>(1,0,0,0),
        Vec4<float>(0,1,0,0),
        Vec4<float>(0,0,1,0),
        Vec4<float>(0,0,0,0));
};
