#include "../include/MyGame.h"
#include "../include/MyEvents.hpp"

DREAM::MyApplication* CreateApplication()
{
	return new MyGame();
}


MyGame::MyGame()
{
	Log::LogMessage("My Game constructor Called");

	

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
		this->gizmoVisibility(false);
		this->setBackGroundColor(COLOR(0.2, 0.2, 0, 1.0f));


		//Custom Shape drawing begins here
		_shapeCreator = new ShapeCreator(basicCamera->getComponent<PhysicsComponent>(),GetRenderSystem(),basicCamera->getComponent<DREAM::CameraComponent>());

}


