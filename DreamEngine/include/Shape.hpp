#pragma once
#include <ECS_Core/Core.hpp>
#include <Component/DrawableComponent.hpp>
#include <Component/VerticesComponent.hpp>
#include <VertexAttribPointerGenerator.hpp>


class Shape
{
	

public:


	static Entity* GetTriangleShape(float _x, float _y, float _z);
	static Entity* GetRectangleShape(float _x, float _y, float _z, float _width, float _height);
	static Entity* GetCubeShape(float _x, float _y, float _z, float _width, float _height, float _depth);
	static Entity* GetLineShape(float _x1, float _y1, float _z1, float _x2, float _y2, float _z2, COLOR _color);
};

