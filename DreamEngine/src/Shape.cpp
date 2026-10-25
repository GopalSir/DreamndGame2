#include "Shape.hpp"


/*
Calculates the direction vectors keeping _v1 as refernce and calculates the cross product. 
*/
PositionComponent<float> Shape::GetFaceNormalUnit(PositionComponent<float> _v1, PositionComponent<float> _v2, PositionComponent<float> _v3)
{

	Vec3<float> a1(_v1.x,_v1.y,_v1.z);
	Vec3<float> a2(_v2.x,_v2.y,_v2.z);
	Vec3<float> a3(_v3.x,_v3.y,_v3.z);

	Vec3<float> dir2 = a2 - a1;
	Vec3<float> dir3 = a3 - a1;

	Vec3<float> result = Vec3<float>::Cross(dir2,dir3); 
	result = Vec3<float>::normalize(result);
	return PositionComponent<float>(result.x,result.y,result.z);
}

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
	VertexAttribPointer* vertexAttrib3 = VertexAttribPointerGenerator::generateVertexAttribPoinnter(VertexAttribPointerGenerator::STYLE::NORMALS);

	DrawableComponent* drbc = new DrawableComponent(DrawableComponent::DRAWABLE_TYPE::TRIANGLE);

	//Vertices themselves will be passed in as 8 vertices, and we will need to generate 12 triangles out of them.
	//The vertices will be passed in as follows:
	
	
	//First I draw the first. Front using first 4 vertices.
	//First Triangle: vertex[0], vertex[1], vertex[2]
	 	verticesComponent->vertices.push_back(_verticesComponent.vertices[0]);
	 verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[0]);


	 	verticesComponent->vertices.push_back(_verticesComponent.vertices[2]);
	 verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[2]);

	 	 verticesComponent->vertices.push_back(_verticesComponent.vertices[1]);
	 verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[1]);

	 PositionComponent<float> n1 = GetFaceNormalUnit(_verticesComponent.vertices[0],_verticesComponent.vertices[2],_verticesComponent.vertices[1]);
	 	



	 //Second Triangle: vertex[0], vertex[2], vertex[3]
	 	verticesComponent->vertices.push_back(_verticesComponent.vertices[0]);
	 verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[0]);


	 	 	verticesComponent->vertices.push_back(_verticesComponent.vertices[3]);
	 verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[3]);

	 	verticesComponent->vertices.push_back(_verticesComponent.vertices[2]);
	 verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[2]);

	 PositionComponent<float>n2 = GetFaceNormalUnit(_verticesComponent.vertices[0],_verticesComponent.vertices[3],_verticesComponent.vertices[2]);


	//Now I draw the back using the last 4 vertices: vertex 4, vertex 5, vertex 6, vertex 7
	//First Triangle
		verticesComponent->vertices.push_back(_verticesComponent.vertices[4]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[4]);


		verticesComponent->vertices.push_back(_verticesComponent.vertices[6]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[6]);

		 verticesComponent->vertices.push_back(_verticesComponent.vertices[5]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[5]);

	 PositionComponent<float> n3 = GetFaceNormalUnit(_verticesComponent.vertices[4],_verticesComponent.vertices[6],_verticesComponent.vertices[5]);




	//Second Triangle

		 verticesComponent->vertices.push_back(_verticesComponent.vertices[4]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[4]);

		 verticesComponent->vertices.push_back(_verticesComponent.vertices[7]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[7]);

		 verticesComponent->vertices.push_back(_verticesComponent.vertices[6]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[6]);


	 //Must match the triangle actually pushed above: 4, 7, 6
	 PositionComponent<float> n4 = GetFaceNormalUnit(_verticesComponent.vertices[4],
	 									_verticesComponent.vertices[7],
	 									_verticesComponent.vertices[6]);



	//Right Face Vertex  3, vertex 2, vertex 5, vertex 4
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[3]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[3]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[5]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[5]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[2]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[2]);

	 PositionComponent<float> n5 = GetFaceNormalUnit(_verticesComponent.vertices[3],
	 									_verticesComponent.vertices[5],
	 									_verticesComponent.vertices[2]);



			 verticesComponent->vertices.push_back(_verticesComponent.vertices[3]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[3]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[4]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[4]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[5]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[5]);

	PositionComponent<float> n6 = GetFaceNormalUnit(_verticesComponent.vertices[3],
	 									_verticesComponent.vertices[4],
	 									_verticesComponent.vertices[5]);



	//Left Face Vertex  7, vertex 6, vertex 2, vertex 1
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[7]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[7]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[1]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[1]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[6]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[6]);

	 PositionComponent<float> n7 = GetFaceNormalUnit(_verticesComponent.vertices[7],
	 									_verticesComponent.vertices[1],
	 									_verticesComponent.vertices[6]);



			 verticesComponent->vertices.push_back(_verticesComponent.vertices[7]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[7]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[0]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[0]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[1]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[1]);

	 PositionComponent<float> n8 = GetFaceNormalUnit(_verticesComponent.vertices[7],
	 									_verticesComponent.vertices[0],
	 									_verticesComponent.vertices[1]);



	//Top Face Vertex vertex 1, vertex 6, vertex 5, vertex 2
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[1]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[1]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[5]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[5]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[6]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[6]);

	 PositionComponent<float> n9 = GetFaceNormalUnit(_verticesComponent.vertices[1],
	 									_verticesComponent.vertices[5],
	 									_verticesComponent.vertices[6]);



			 verticesComponent->vertices.push_back(_verticesComponent.vertices[1]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[1]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[2]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[2]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[5]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[5]);

	 PositionComponent<float> n10 = GetFaceNormalUnit(_verticesComponent.vertices[1],
	 									_verticesComponent.vertices[2],
	 									_verticesComponent.vertices[5]);




		//Bottom  Face Vertex vertex 7, vertex 0, vertex 3, vertex 6
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[7]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[7]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[3]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[3]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[0]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[0]);

	 PositionComponent<float> n11 = GetFaceNormalUnit(_verticesComponent.vertices[7],
	 									_verticesComponent.vertices[3],
	 									_verticesComponent.vertices[0]);



			 verticesComponent->vertices.push_back(_verticesComponent.vertices[7]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[7]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[4]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[4]);
			 verticesComponent->vertices.push_back(_verticesComponent.vertices[3]);
	verticesComponent->vertices_color.push_back(_verticesComponent.vertices_color[3]);

	 PositionComponent<float> n12 = GetFaceNormalUnit(_verticesComponent.vertices[7],
	 									_verticesComponent.vertices[4],
	 									_verticesComponent.vertices[3]);

	 verticesComponent->normals.push_back(n1);
	 verticesComponent->normals.push_back(n1);
	 verticesComponent->normals.push_back(n1);

	 verticesComponent->normals.push_back(n2);
	 verticesComponent->normals.push_back(n2);
	 verticesComponent->normals.push_back(n2);

	 verticesComponent->normals.push_back(n3);
	 verticesComponent->normals.push_back(n3);
	 verticesComponent->normals.push_back(n3);

	 verticesComponent->normals.push_back(n4);
	 verticesComponent->normals.push_back(n4);
	 verticesComponent->normals.push_back(n4);

	 verticesComponent->normals.push_back(n5);
	 verticesComponent->normals.push_back(n5);
	 verticesComponent->normals.push_back(n5);

	 verticesComponent->normals.push_back(n6);
	 verticesComponent->normals.push_back(n6);
	 verticesComponent->normals.push_back(n6);

	 verticesComponent->normals.push_back(n7);
	 verticesComponent->normals.push_back(n7);
	 verticesComponent->normals.push_back(n7);

	 verticesComponent->normals.push_back(n8);
	 verticesComponent->normals.push_back(n8);
	 verticesComponent->normals.push_back(n8);

	 verticesComponent->normals.push_back(n9);
	 verticesComponent->normals.push_back(n9);
	 verticesComponent->normals.push_back(n9);

	 verticesComponent->normals.push_back(n10);
	 verticesComponent->normals.push_back(n10);
	 verticesComponent->normals.push_back(n10);

	 verticesComponent->normals.push_back(n11);
	 verticesComponent->normals.push_back(n11);
	 verticesComponent->normals.push_back(n11);

	 verticesComponent->normals.push_back(n12);
	 verticesComponent->normals.push_back(n12);
	 verticesComponent->normals.push_back(n12);


	verticesComponent->vertexAttributePointers.push_back(vertexAttrib1);
	verticesComponent->vertexAttributePointers.push_back(vertexAttrib2);
	verticesComponent->vertexAttributePointers.push_back(vertexAttrib3);




	_entity->addComponent(verticesComponent);
	_entity->addComponent(drbc);
	
}


