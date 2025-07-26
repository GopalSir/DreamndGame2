#include "Shape.hpp"

//Shape::Shape()
//{
//	drawableComponent = DrawableComponent();
//	vertexAttributeComponent = VertexAttribPointerGenerator::generateVertexAttribPoinnter(
//									VertexAttribPointerGenerator::STYLE::DEFAULT);
//
//}

Entity* Shape::GetShape(SHAPE_TYPE _shapeType)
{
	VerticesComponent<float>* verticesComponent = new VerticesComponent<float>();
	DrawableComponent* drawableComponent = new DrawableComponent;
	VertexAttribComponent* vertexAttributeComponent =  VertexAttribPointerGenerator::generateVertexAttribPoinnter(VertexAttribPointerGenerator::STYLE::DEFAULT);
	Entity* result = new Entity();
	if (_shapeType == SHAPE_TYPE::TRIANGLE)
	{
		
		verticesComponent->vertices.push_back( PositionComponent<float>(100, 100, 0));
		verticesComponent->vertices.push_back(PositionComponent<float>(100, 200, 0));
		verticesComponent->vertices.push_back(PositionComponent<float>(200, 200, 0));

		
		result->addComponent(verticesComponent);
		result->addComponent(drawableComponent);
		result->addComponent(vertexAttributeComponent);



	}
	else if (_shapeType == SHAPE_TYPE::RECTANGLE)
	{

		//Default values will be normalized
		verticesComponent->vertices.push_back(PositionComponent<float>(100, 100, 0));
		verticesComponent->vertices.push_back(PositionComponent<float>(100, 200, 0));
		verticesComponent->vertices.push_back(PositionComponent<float>(200, 200, 0));


		verticesComponent->vertices.push_back(PositionComponent<float>(100, 100, 0));
		verticesComponent->vertices.push_back(PositionComponent<float>(200, 200, 0));
		verticesComponent->vertices.push_back(PositionComponent<float>(200, 100, 0));


		result->addComponent(verticesComponent);
		result->addComponent(drawableComponent);
		result->addComponent(vertexAttributeComponent);
		
	}
	else if (_shapeType == SHAPE_TYPE::CUBE)
	{
		//Default values will be normalized
	

// Front face
		verticesComponent->vertices.push_back(PositionComponent<float>(-50, -50, 50));
		verticesComponent->vertices.push_back(PositionComponent<float>(-50, 50, 50));
		verticesComponent->vertices.push_back(PositionComponent<float>(50, 50, 50));

		verticesComponent->vertices.push_back(PositionComponent<float>(-50, -50, 50));
		verticesComponent->vertices.push_back(PositionComponent<float>(50, 50, 50));
		verticesComponent->vertices.push_back(PositionComponent<float>(50, -50, 50));

		// Back face
		verticesComponent->vertices.push_back(PositionComponent<float>(-50, -50, -50));
		verticesComponent->vertices.push_back(PositionComponent<float>(50, 50, -50));
		verticesComponent->vertices.push_back(PositionComponent<float>(-50, 50, -50));

		verticesComponent->vertices.push_back(PositionComponent<float>(-50, -50, -50));
		verticesComponent->vertices.push_back(PositionComponent<float>(50, -50, -50));
		verticesComponent->vertices.push_back(PositionComponent<float>(50, 50, -50));

		// Top face
		verticesComponent->vertices.push_back(PositionComponent<float>(-50, 50, 50));
		verticesComponent->vertices.push_back(PositionComponent<float>(-50, 50, -50));
		verticesComponent->vertices.push_back(PositionComponent<float>(50, 50, -50));

		verticesComponent->vertices.push_back(PositionComponent<float>(-50, 50, 50));
		verticesComponent->vertices.push_back(PositionComponent<float>(50, 50, -50));
		verticesComponent->vertices.push_back(PositionComponent<float>(50, 50, 50));

		// Bottom face
		verticesComponent->vertices.push_back(PositionComponent<float>(-50, -50, 50));
		verticesComponent->vertices.push_back(PositionComponent<float>(50, -50, -50));
		verticesComponent->vertices.push_back(PositionComponent<float>(-50, -50, -50));

		verticesComponent->vertices.push_back(PositionComponent<float>(-50, -50, 50));
		verticesComponent->vertices.push_back(PositionComponent<float>(50, -50, 50));
		verticesComponent->vertices.push_back(PositionComponent<float>(50, -50, -50));

		// Left face
		verticesComponent->vertices.push_back(PositionComponent<float>(-50, -50, 50));
		verticesComponent->vertices.push_back(PositionComponent<float>(-50, -50, -50));
		verticesComponent->vertices.push_back(PositionComponent<float>(-50, 50, -50));

		verticesComponent->vertices.push_back(PositionComponent<float>(-50, -50, 50));
		verticesComponent->vertices.push_back(PositionComponent<float>(-50, 50, -50));
		verticesComponent->vertices.push_back(PositionComponent<float>(-50, 50, 50));

		// Right face
		verticesComponent->vertices.push_back(PositionComponent<float>(50, -50, 50));
		verticesComponent->vertices.push_back(PositionComponent<float>(50, 50, -50));
		verticesComponent->vertices.push_back(PositionComponent<float>(50, -50, -50));

		verticesComponent->vertices.push_back(PositionComponent<float>(50, -50, 50));
		verticesComponent->vertices.push_back(PositionComponent<float>(50, 50, 50));
		verticesComponent->vertices.push_back(PositionComponent<float>(50, 50, -50));







		result->addComponent(verticesComponent);
		result->addComponent(drawableComponent);
		result->addComponent(vertexAttributeComponent);

	}
	return result;
}
