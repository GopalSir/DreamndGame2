#include "Shape.hpp"



void Shape::BuildPointShape(Entity* _entity,DREAM::VerticesComponent<float>& _verticesComponent)
{
	DREAM::VerticesComponent<float>* verticesComponent = new DREAM::VerticesComponent<float>();
	*verticesComponent = _verticesComponent;
	
	VertexAttribPointer* vertexAttributePositionPointer = VertexAttribPointerGenerator::generateVertexAttribPoinnter(VertexAttribPointerGenerator::STYLE::VERTEX);
	VertexAttribPointer* vertexAttributeColorPointer = VertexAttribPointerGenerator::generateVertexAttribPoinnter(VertexAttribPointerGenerator::STYLE::COLOR);
	
	// Attach vertex attribute pointers
	verticesComponent->vertexAttributePointers.push_back(vertexAttributePositionPointer);
	verticesComponent->vertexAttributePointers.push_back(vertexAttributeColorPointer);
	
	DrawableComponent* drawableComponent = new DrawableComponent(DrawableComponent::DRAWABLE_TYPE::POINT);

	_entity->addComponent(verticesComponent);
	_entity->addComponent(drawableComponent);

}



void Shape::BuildLineShape(Entity* _entity,float _x1, float _y1, float _z1, float _x2, float _y2, float _z2, COLOR _color)
{
	DREAM::VerticesComponent<float>* verticesComponent = new DREAM::VerticesComponent<float>();
	VertexAttribPointer* vertexAttributeComponent = VertexAttribPointerGenerator::generateVertexAttribPoinnter(VertexAttribPointerGenerator::STYLE::VERTEX);
	VertexAttribPointer* vertexAttributeColorPointer = VertexAttribPointerGenerator::generateVertexAttribPoinnter(VertexAttribPointerGenerator::STYLE::COLOR);

	DrawableComponent* drawableComponent = new DrawableComponent(DrawableComponent::DRAWABLE_TYPE::LINE);
	drawableComponent->color = _color;

	

	verticesComponent->vertices.push_back(PositionComponent<float>(_x1, _y1, _z1));
	verticesComponent->vertices.push_back(PositionComponent<float>(_x2, _y2, _z2));

	verticesComponent->vertices_color.push_back(_color);
	verticesComponent->vertices_color.push_back(_color);



	verticesComponent->vertexAttributePointers.push_back(vertexAttributeComponent);
	verticesComponent->vertexAttributePointers.push_back(vertexAttributeColorPointer);


	_entity->addComponent(verticesComponent);
	_entity->addComponent(drawableComponent);

}

//Incomplete and wrong
void Shape::BuildTriangleShape(Entity* _entity,DREAM::VerticesComponent<float> &_verticesComponent)
{
	DREAM::VerticesComponent<float>* verticesComponent = new DREAM::VerticesComponent<float>();
	*verticesComponent = _verticesComponent;

	VertexAttribPointer* vertexAttributePositionPOinter = VertexAttribPointerGenerator::generateVertexAttribPoinnter(VertexAttribPointerGenerator::STYLE::VERTEX);
	VertexAttribPointer* vertexAttributeColorPointer = VertexAttribPointerGenerator::generateVertexAttribPoinnter(VertexAttribPointerGenerator::STYLE::COLOR);
	VertexAttribPointer* vertexAttributeNormalPointer = VertexAttribPointerGenerator::generateVertexAttribPoinnter(VertexAttribPointerGenerator::STYLE::NORMALS);

	DrawableComponent* drawableComponent = new DrawableComponent(DrawableComponent::DRAWABLE_TYPE::TRIANGLE);

	verticesComponent->vertexAttributePointers.push_back(vertexAttributePositionPOinter);
	verticesComponent->vertexAttributePointers.push_back(vertexAttributeColorPointer);
	verticesComponent->vertexAttributePointers.push_back(vertexAttributeNormalPointer);

	

	_entity->addComponent(verticesComponent);   
	_entity->addComponent(drawableComponent);

}

void Shape::BuildRectangleShape(Entity* _entity,DREAM::VerticesComponent<float>& _verticesComponent)
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
		throw std::runtime_error("Cannot generate Rectangle as size of vertices is not divisible by 4");
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

	_entity->addComponent(verticesComponent);
	_entity->addComponent(drawableComponent);

}

// Takes in pointer to entity and attaches the vertices component and drawable component to the entity. 
void Shape::BuildCubeShape(Entity* _entity, DREAM::VerticesComponent<float>& _verticesComponent)
{

	//We will need a pointer to the vertices component
	DREAM::VerticesComponent<float>* verticesComponent  = new DREAM::VerticesComponent<float>();
	
	VertexAttribPointer* vertexAttrib1 = VertexAttribPointerGenerator::generateVertexAttribPoinnter(VertexAttribPointerGenerator::VERTEX);
	VertexAttribPointer* vertexAttrib2 = VertexAttribPointerGenerator::generateVertexAttribPoinnter(VertexAttribPointerGenerator::COLOR);

	DrawableComponent* drbc = new DrawableComponent(DrawableComponent::DRAWABLE_TYPE::TRIANGLE);

	//Vertices themselves will be passed in as 8 vertices, and we will need to generate 12 triangles out of them.
	//The vertices will be passed in as follows:
	
	
	//First I draw the first. Front using first 4 vertices.
	//First Triangle: vertex[0], vertex[1], vertex[2]
	 verticesComponent->vertices.push_back(_verticesComponent.vertices[0]);
	 verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[0]);

	 verticesComponent->vertices.push_back(_verticesComponent.vertices[1]);
	 verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[1]);

	 verticesComponent->vertices.push_back(_verticesComponent.vertices[2]);
	 verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[2]);

	 //Second Triangle: vertex[0], vertex[2], vertex[3]
	 verticesComponent->vertices.push_back(_verticesComponent.vertices[0]);
	 verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[0]);

	 verticesComponent->vertices.push_back(_verticesComponent.vertices[2]);
	 verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[2]);

	 verticesComponent->vertices.push_back(_verticesComponent.vertices[3]);
	 verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[3]);

	//Now I draw the back using the last 4 vertices: vertex 4, vertex 5, vertex 6, vertex 7
	//First Triangle
	verticesComponent->vertices.push_back(_verticesComponent.vertices[4]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[4]);

		 verticesComponent->vertices.push_back(_verticesComponent.vertices[5]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[5]);


		 verticesComponent->vertices.push_back(_verticesComponent.vertices[6]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[6]);


	//Second Triangle

		 verticesComponent->vertices.push_back(_verticesComponent.vertices[4]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[4]);

		 verticesComponent->vertices.push_back(_verticesComponent.vertices[6]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[6]);

		 verticesComponent->vertices.push_back(_verticesComponent.vertices[7]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[7]);

	//Right Face Vertex  3, vertex 2, vertex 5, vertex 4
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[3]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[3]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[2]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[2]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[5]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[5]);

			 verticesComponent->vertices.push_back(_verticesComponent.vertices[3]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[3]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[5]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[5]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[4]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[4]);


	verticesComponent->vertexAttributePointers.push_back(vertexAttrib1);
	verticesComponent->vertexAttributePointers.push_back(vertexAttrib2);





	_entity->addComponent(verticesComponent);
	_entity->addComponent(drbc);
	
}

void Shape::CalculateVertexNormals(const DREAM::VerticesComponent<float>& _vc )
{
	//Clockwise verti
}
