#pragma once
#include <ECS_Core/Core.hpp>

template<typename T>
class RotationComponent: public Component
{
    /*Three positional components. Class is of template type. Code will be generated when type is supplied*/
    T x,y,z;

    public:
    //Default Constructor
    RotationComponent();
    RotationComponent(T _x, T _y, T _z);

};

template <typename T>
 RotationComponent<T>::RotationComponent()
{
    x = 0;
    y = 0;
    z = 0;
}

template <typename T>
 RotationComponent<T>::RotationComponent(T _x, T _y, T _z)
{
    x = _x;
    y = _y;
    z = _z;
}
