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
		MyApplication::addGameSystem(new PlayerSystem());


		setupEntities();
		setupFloorEntity();


		

}

void MyGame::setupShaders(){
	
	//Set up shaders for the program
	basicShader = new Shader("shaders/BasicVertexShader.glsl", "shaders/BasicFragmentShader.glsl");
	basicShader->setUniform(basicShader->programID, "light_position", 0.0f, -0.0f, 0.0f, 1.0f);
		


    
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
	
	Shape::CalculateVertexNormals(vc);
	floorEntity->getComponent<DrawableComponent>()->shaderProgramID = basicShader->programID;
	MyApplication::RegisterEntity(floorEntity);

}




