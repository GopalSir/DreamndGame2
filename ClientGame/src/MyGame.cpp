// MyGame and event headers
#include "../include/MyGame.h"
#include "../include/MyEvents.hpp"

DREAM::MyApplication* CreateApplication()
{
	return new MyGame();
}


MyGame::MyGame()
{
	Log::LogMessage("My Game constructor Called");

		Entity* basicCamera = CreateEntity();
		DREAM::CameraSystem::createDefaultCamera(basicCamera);
		basicCamera->addComponent(new DREAM::CameraControllerComponent());
		GetCameraSystem()->addEntity(basicCamera);

	DREAM::EventSystem::registerEvent(DREAM::MouseClickEvent::GetEventTypeCode(), basicCamera->getComponent<DREAM::CameraControllerComponent>());
	DREAM::EventSystem::registerEvent(DREAM::KeyPressEvent::GetEventTypeCode(), basicCamera->getComponent<DREAM::CameraControllerComponent>());
	DREAM::EventSystem::registerEvent(DREAM::KeyReleaseEvent::GetEventTypeCode(), basicCamera->getComponent<DREAM::CameraControllerComponent>());
	// Camera scroll disabled - Lua scripts handle scroll for fractal zoom
	// DREAM::EventSystem::registerEvent(DREAM::MouseScrollEvent::GetEventTypeCode(), basicCamera->getComponent<DREAM::CameraControllerComponent>());
	DREAM::EventSystem::registerEvent(DREAM::MouseMoveEvent::GetEventTypeCode(), basicCamera->getComponent<DREAM::CameraControllerComponent>());
		//Will Implement this in DreamEngine. 
		/*This function will add or remove 3 axis lines from the scene. basically add lines or remove lines from the render system queue*/
	
	//Set up shaders for the program
	setupShaders();

	
		MyApplication::setupGizmo();




				//setup systems 
		//MyApplication::addGameSystem(new PlayerSystem());
		MyApplication::addGameSystem(new CollisionSystem());


		setupEntities();
		setupFloorEntity();


		

}

void MyGame::setupShaders(){
	
	//Set up shaders for the program
	basicShader = new Shader("shaders/BasicVertexShader.glsl", "shaders/BasicFragmentShader.glsl");
	basicShader->setUniform(basicShader->programID, "light_position", 0.0f, 20.0f, 0.0f, 1.0f);
		


    
	//Set up shaders for the program
	//GetRenderSystem()->setDefaultShaders(basicVertex, basicFragment);
}

void MyGame::setupEntities(){
	//Set up entities for the program
	Entity* triangleEntity = CreateEntity();

	VerticesComponent<float> vc = VerticesComponent<float>();
	vc.vertices.push_back(PositionComponent<float>(-0.5f, -0.5f, 0.0f));
	vc.vertices.push_back(PositionComponent<float>(0.5f, -0.5f, 0.0f));
	vc.vertices.push_back(PositionComponent<float>(0.0f, 0.5f, 0.0f));

	vc.vertices_color.push_back(COLOR(1.0f, 0.0f, 0.0f, 1.0f));
	vc.vertices_color.push_back(COLOR(0.0f, 1.0f, 0.0f, 1.0f));
	vc.vertices_color.push_back(COLOR(0.0f, 0.0f, 1.0f, 1.0f));

	Shape::BuildTriangleShape(triangleEntity, vc);

	

	triangleEntity->addComponent(new DREAM::PhysicsComponent(Vec4<float>(0.0f, 0.0f, 0.0f, 1.0f), 
															Vec4<float>(0.0f, 0.0f, 0.0f, 1.0f), 
															Vec4<float>(0.0f, 0.0f, 0.0f, 1.0f), 
															Vec4<float>(0.0f, 0.0f, 0.0f, 1.0f)));

	

	MyApplication::RegisterEntity(triangleEntity);


	//Setting up cube entity
	Entity* cubeEntity = CreateEntity();
	VerticesComponent<float> cubeVertices = VerticesComponent<float>();

	//adding the vertices ony by one
	//Centred on the origin so the visual cube and the box collider share the
	//same frame: corners sit at +-1, matching half_extents of (1,1,1).
	cubeVertices.vertices.push_back(PositionComponent<float>(-1,-1, 1));
	cubeVertices.vertices.push_back(PositionComponent<float>(-1, 1, 1));
	cubeVertices.vertices.push_back(PositionComponent<float>( 1, 1, 1));
	cubeVertices.vertices.push_back(PositionComponent<float>( 1,-1, 1));
	cubeVertices.vertices.push_back(PositionComponent<float>( 1,-1,-1));
	cubeVertices.vertices.push_back(PositionComponent<float>( 1, 1,-1));
	cubeVertices.vertices.push_back(PositionComponent<float>(-1, 1,-1));
	cubeVertices.vertices.push_back(PositionComponent<float>(-1,-1,-1));

	cubeVertices.vertices_color.push_back(COLOR(1,0,0,1));
	cubeVertices.vertices_color.push_back(COLOR(1,0,0,1));
	cubeVertices.vertices_color.push_back(COLOR(1,0,0,1));
	cubeVertices.vertices_color.push_back(COLOR(1,0,0,1));
	cubeVertices.vertices_color.push_back(COLOR(1,0,0,1));
	cubeVertices.vertices_color.push_back(COLOR(1,0,0,1));
	cubeVertices.vertices_color.push_back(COLOR(1,0,0,1));
	cubeVertices.vertices_color.push_back(COLOR(1,0,0,1));




	Shape::BuildCubeShape(cubeEntity,cubeVertices);

	cubeEntity->addComponent(new DREAM::PhysicsComponent(Vec4<float>(0.0f, 0.0f, 0.0f, 1.0f), 
															Vec4<float>(0.0f, 10.0f, 0.0f, 1.0f), 
															Vec4<float>(0.0f, 0.0f, 0.0f, 1.0f), 
															Vec4<float>(0.0f, 0.0f, 0.0f, 1.0f),
															true));
	cubeEntity->addComponent(new ColliderComponent(
		ColliderType::BOX,
		Vec3<float>(1,1,1),
		Vec3<float>(0,1,0),
		0.0f));

	cubeEntity->getComponent<DrawableComponent>()->shaderProgramID = basicShader->programID;
	RegisterEntity(cubeEntity);







}

void MyGame::setupFloorEntity()
{
	Entity* floorEntity = CreateEntity();

	VerticesComponent<float> vc = VerticesComponent<float>();
	vc.vertices.push_back(PositionComponent<float>(-100.0f, -1.0f, -100.0f));
	vc.vertices.push_back(PositionComponent<float>(100.0f, -1.0f, -100.0f));
	vc.vertices.push_back(PositionComponent<float>(100.0f, -1.0f, 100.0f));

	vc.vertices.push_back(PositionComponent<float>(-100.0f, -1.0f, -100.0f));
	vc.vertices.push_back(PositionComponent<float>(100.0f, -1.0f, 100.0f));
	vc.vertices.push_back(PositionComponent<float>(-100.0f, -1.0f, 100.0f));

	vc.normals.push_back(PositionComponent<float>(0,1,0));
	vc.normals.push_back(PositionComponent<float>(0,1,0));
	vc.normals.push_back(PositionComponent<float>(0,1,0));

	vc.normals.push_back(PositionComponent<float>(0,1,0));
	vc.normals.push_back(PositionComponent<float>(0,1,0));
	vc.normals.push_back(PositionComponent<float>(0,1,0));




	vc.vertices_color.push_back(COLOR(0.5f, 0.5f, 0.5f, 1.0f));
	vc.vertices_color.push_back(COLOR(0.5f, 0.5f, 0.5f, 1.0f));
	vc.vertices_color.push_back(COLOR(0.5f, 0.5f, 0.5f, 1.0f));
	vc.vertices_color.push_back(COLOR(0.5f, 0.5f, 0.5f, 1.0f));
	vc.vertices_color.push_back(COLOR(0.5f, 0.5f, 0.5f, 1.0f));
	vc.vertices_color.push_back(COLOR(0.5f, 0.5f, 0.5f, 1.0f));	

	Shape::BuildTriangleShape(floorEntity, vc);
	
	//TODO: Shape::CalculateVertexNormals(vc) - never implemented. Would also be a no-op
	//here: BuildTriangleShape already copied vc into the entity, so mutating the local
	//vc afterwards can't reach it. Normals are hand-pushed above for now.
	floorEntity->getComponent<DrawableComponent>()->shaderProgramID = basicShader->programID;
	MyApplication::RegisterEntity(floorEntity);

}




