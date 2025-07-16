#pragma once
#include <ECS_Core/Core.hpp>
#include <Component/DrawableComponent.hpp>
#include <Component/VerticesComponent.hpp>
#include <VertexAttribPointerGenerator.hpp>


class Shape
{
	

public:
	enum SHAPE_TYPE
	{
		POINT,
		TRIANGLE,
		RECTANGLE,
		CUBE
	};
	static Entity* GetShape(SHAPE_TYPE);
};

