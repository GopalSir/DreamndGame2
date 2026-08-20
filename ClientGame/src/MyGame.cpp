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

		setupEntities();

}

void MyGame::setupShaders(){
	
	//Set up shaders for the program
	basicShader = new Shader("shaders/BasicVertexShader.glsl", "shaders/BasicFragmentShader.glsl");
		


    
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

	int entity_id1 = GetRenderSystem()->addEntity(triangleEntity);
	GetRenderSystem()->initEntityBuffers(entity_id1);
}




