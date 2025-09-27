#include "Shape.hpp"



Entity* Shape::GetPointShape(float _x, float _y, float _z, COLOR _color)
{
	DREAM::VerticesComponent<float>* verticesComponent = new DREAM::VerticesComponent<float>();
	//VertexAttribComponent* vertexAttributeComponent = VertexAttribPointerGenerator::generateVertexAttribPoinnter(VertexAttribPointerGenerator::STYLE::DEFAULT);
	DrawableComponent* drawableComponent = new DrawableComponent(DrawableComponent::DRAWABLE_TYPE::POINT);
	drawableComponent->color = _color;

	Entity* result = new Entity();

	verticesComponent->vertices.push_back(PositionComponent<float>(_x, _y, _z));

	result->addComponent(verticesComponent);
	result->addComponent(drawableComponent);

	return result;
}



Entity* Shape::GetLineShape(float _x1, float _y1, float _z1, float _x2, float _y2, float _z2, COLOR _color)
{
	DREAM::VerticesComponent<float>* verticesComponent = new DREAM::VerticesComponent<float>();
	//VertexAttribComponent* vertexAttributeComponent = VertexAttribPointerGenerator::generateVertexAttribPoinnter(VertexAttribPointerGenerator::STYLE::DEFAULT);
	DrawableComponent* drawableComponent = new DrawableComponent(DrawableComponent::DRAWABLE_TYPE::LINE);
	drawableComponent->color = _color;

	Entity* result = new Entity();

	verticesComponent->vertices.push_back(PositionComponent<float>(_x1, _y1, _z1));
	verticesComponent->vertices.push_back(PositionComponent<float>(_x2, _y2, _z2));

	result->addComponent(verticesComponent);
	//result->addComponent(vertexAttributeComponent);
	result->addComponent(drawableComponent);

	return result;
}

//Incomplete and wrong
Entity* Shape::GetTriangleShape(DREAM::VerticesComponent<float> &_verticesComponent)
{
	DREAM::VerticesComponent<float>* verticesComponent = new DREAM::VerticesComponent<float>();
	*verticesComponent = _verticesComponent;

	VertexAttribPointer* vertexAttributePositionPOinter = VertexAttribPointerGenerator::generateVertexAttribPoinnter(VertexAttribPointerGenerator::STYLE::VERTEX);
	VertexAttribPointer* vertexAttributeColorPointer = VertexAttribPointerGenerator::generateVertexAttribPoinnter(VertexAttribPointerGenerator::STYLE::COLOR);

	DrawableComponent* drawableComponent = new DrawableComponent(DrawableComponent::DRAWABLE_TYPE::TRIANGLE);

	Entity* result = new Entity();

	result->addComponent(verticesComponent);   
	result->addComponent(drawableComponent);

	return result;
}

Entity* Shape::GetRectangleShape(DREAM::VerticesComponent<float>& _verticesComponent)
{
	//We will need to make 6 vertices out of 4 vertices, and render this as 2 triangles. 
	/*
	 1st Triangle: vertex[0], vertex[1], vertex[2]
	 2nd Triangle: vertex[0], vertex[2], vertex[3]
	*/
	if (_verticesComponent.vertices.size()%4 != 0 )
	{
		std::cout << "Cannot generat Rectangle as size of vertices is not divisible by 4\n";
		std::cout << "Size of cities vertices: " << _verticesComponent.vertices.size();
		return nullptr;
	}

	DREAM::VerticesComponent<float>* verticesComponent = new DREAM::VerticesComponent<float>();
	VertexAttribPointer* vertexAttributePositionPOinter = VertexAttribPointerGenerator::generateVertexAttribPoinnter(VertexAttribPointerGenerator::STYLE::VERTEX);
	VertexAttribPointer* vertexAttributeColorPointer = VertexAttribPointerGenerator::generateVertexAttribPoinnter(VertexAttribPointerGenerator::STYLE::COLOR);
	
	for (int i = 0; i < _verticesComponent.vertices.size(); i += 4)
	{
			//1st triangle
		verticesComponent->vertices.push_back(_verticesComponent.vertices[i + 0]);
		verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[i+ 0]);


		verticesComponent->vertices.push_back(_verticesComponent.vertices[i + 1]);
		verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[i + 1]);

		verticesComponent->vertices.push_back(_verticesComponent.vertices[i + 2]);
		verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[i + 2]);


		//2nd triangle
		verticesComponent->vertices.push_back(_verticesComponent.vertices[i + 0]);
		verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[i + 0]);

		verticesComponent->vertices.push_back(_verticesComponent.vertices[i + 2]);
		verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[i + 2]);

		verticesComponent->vertices.push_back(_verticesComponent.vertices[i + 3]);
		verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[i + 3]);
	}



	//Setting vertex attribute position and vertex attribute color information 

	verticesComponent->vertexAttributePointers.push_back(vertexAttributePositionPOinter);
	verticesComponent->vertexAttributePointers.push_back(vertexAttributeColorPointer);




	DrawableComponent* drawableComponent = new DrawableComponent(DrawableComponent::DRAWABLE_TYPE::TRIANGLE);

	Entity* result = new Entity();

	result->addComponent(verticesComponent);
	result->addComponent(drawableComponent);

	return result;
}