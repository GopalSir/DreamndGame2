#include "../include/MyGame.h"
#include "../include/MyEvents.hpp"

DREAM::MyApplication* CreateApplication()
{
	return new MyGame();
}


MyGame::MyGame()
{
	Log::LogMessage("My Game constructor Called");

	int a = 10;

	ThrusterComponent* thrusterComponent = new ThrusterComponent();

	DREAM::EventSystem::registerEvent(PlaneCrashEvent::GetEventTypeCode(), thrusterComponent);

	if (a == 10)
	{

		PlaneCrashEvent* planeCrashEvent = new PlaneCrashEvent();
		DREAM::EventSystem::handleEvent(planeCrashEvent);
		delete planeCrashEvent;
	}
	

	//Entity* basicCube = Shape::GetShape(Shape::SHAPE_TYPE::CUBE);
	//


	//	int index1 = this->GetRenderSystem()->addEntity(basicCube);
	//	this->GetRenderSystem()->initEntityBuffers(index1);

		Entity* basicCamera = DREAM::CameraSystem::createDefaultCameraEntity();
		basicCamera->addComponent(new DREAM::CameraControllerComponent());
		GetCameraSystem()->addEntity(basicCamera);

		DREAM::EventSystem::registerEvent(DREAM::MouseClickEvent::GetEventTypeCode(), basicCamera->getComponent<DREAM::CameraControllerComponent>());
		DREAM::EventSystem::registerEvent(DREAM::KeyPressEvent::GetEventTypeCode(), basicCamera->getComponent<DREAM::CameraControllerComponent>());
		DREAM::EventSystem::registerEvent(DREAM::KeyReleaseEvent::GetEventTypeCode(), basicCamera->getComponent<DREAM::CameraControllerComponent>());
		DREAM::EventSystem::registerEvent(DREAM::MouseScrollEvent::GetEventTypeCode(), basicCamera->getComponent<DREAM::CameraControllerComponent>());
		DREAM::EventSystem::registerEvent(DREAM::MouseMoveEvent::GetEventTypeCode(), basicCamera->getComponent<DREAM::CameraControllerComponent>());
		//Will Implement this in DreamEngine. 
		/*This function will add or remove 3 axis lines from the scene. basically add lines or remove lines from the render system queue*/
		this->gizmoVisibility(true);


		//Custom Shape drawing begins here
		_shapeCreator = new ShapeCreator(basicCamera->getComponent<PhysicsComponent>(),GetRenderSystem(),basicCamera->getComponent<DREAM::CameraComponent>());

		DREAM::EventSystem::registerEvent(DREAM::MouseClickEvent::GetEventTypeCode(), _shapeCreator);
		DREAM::EventSystem::registerEvent(DREAM::KeyPressEvent::GetEventTypeCode(), _shapeCreator);


	
		GenerateBird();

}

void MyGame::GenerateBird()
{
	VerticesComponent<float> birdVertices;

	float x1, y1, z1;

	x1 = 0.0f;
	y1 = 100;
	z1 = 0;

	
	birdVertices.vertices.push_back(PositionComponent<float>(x1, y1, z1));
	birdVertices.vertices.push_back(PositionComponent<float>(x1, y1+30, z1));
	birdVertices.vertices.push_back(PositionComponent<float>(x1+30, y1+15, z1));

	Entity* bird = Shape::GetTriangleShape(birdVertices);
	int entity_index = MyApplication::GetRenderSystem()->addEntity(bird);
	MyApplication::GetRenderSystem()->initEntityBuffers(entity_index);

	bird->addComponent(new PhysicsComponent());
	MyApplication::GetPhysicsSystem()->addEntity(bird);

	bird->getComponent<PhysicsComponent>()->velocity.x = 10.0f;

}
