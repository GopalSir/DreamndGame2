#pragma once
#include <ECS_Core/Core.hpp>

template<typename T>
class PositionComponent: public Component
{
    

    public:
    /*Three positional components. Class is of template type. Code will be generated when type is supplied*/
    T x,y,z;
    //Default Constructor
    PositionComponent();
    PositionComponent(T _x, T _y, T _z);

};

template <typename T>
 PositionComponent<T>::PositionComponent()
{
    x = 0;
    y = 0;
    z = 0;
}

template <typename T>
 PositionComponent<T>::PositionComponent(T _x, T _y, T _z)
{
    x = _x;
    y = _y;
    z = _z;
};
