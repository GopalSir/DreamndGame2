#pragma once
#include <ECS_Core/Core.hpp>
#include <Component/DrawableComponent.hpp>
#include <Component/VerticesComponent.hpp>
#include <VertexAttribPointerGenerator.hpp>



class Shape
{
	

public:

	static void BuildPointShape(Entity* _entity,DREAM::VerticesComponent<float>& _verticesComponent);
	static void BuildTriangleShape(Entity* _entity,DREAM::VerticesComponent<float> &_verticesComponent);
	static void BuildRectangleShape(Entity* _entity,DREAM::VerticesComponent<float>& _verticesComponent);
	
	static void BuildCubeShape(Entity* _entity,DREAM::VerticesComponent<float>& _verticesComponent);
	static void BuildLineShape(Entity* _entity,float _x1, float _y1, float _z1, float _x2, float _y2, float _z2, COLOR _color);

	static void  CalculateVertexNormals(const DREAM::VerticesComponent<float>& _verticesComponent);
};

