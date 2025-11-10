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
		//_shapeCreator = new ShapeCreator(basicCamera->getComponent<PhysicsComponent>(),GetRenderSystem(),basicCamera->getComponent<DREAM::CameraComponent>());

		//int heightMap[10][10];

		////heightmap is done
		//for (int i = 0; i < 10; ++i)
		//{
		//	for (int j = 0; j < 10; ++j)
		//	{
		//		heightMap[i][j] = 20 - (i + j);
		//	}
		//}
		
		int rect_count_x = 500;
		int rect_count_y = 500;

		int length = 1;
		int breadth = 1;

		float max_height = 50;

		float max_x_position = rect_count_x * breadth;
		float max_y_position = rect_count_y * length;

		float x_frequency = 10;
		float y_frequency = 5;

		DREAM::VerticesComponent<float>vc;

		for (int i = 0; i < rect_count_x; ++i)
		{
			for (int j = 0; j < rect_count_y; ++j)
			{

				PositionComponent<float> v1, v2, v3, v4;
				v1.x = i * breadth;
				v1.y = j * length;
				v1.z = MountainGenerator::SampleRidgeHeight(v1.x, v1.y, max_x_position, max_y_position, x_frequency, max_height);

				//calculate v2,v3,v4;
						// bottom-right
				v2.x = (i + 1) * breadth;
				v2.y = j * length;
				v2.z = MountainGenerator::SampleRidgeHeight(v2.x, v2.y, max_x_position, max_y_position, x_frequency, max_height);

				// top-right
				v3.x = (i + 1) * breadth;
				v3.y = (j + 1) * length;
				v3.z = MountainGenerator::SampleRidgeHeight(v3.x, v3.y, max_x_position, max_y_position, x_frequency, max_height);

				// top-left
				v4.x = i * breadth;
				v4.y = (j + 1) * length;
				v4.z = MountainGenerator::SampleRidgeHeight(v4.x, v4.y, max_x_position, max_y_position, x_frequency, max_height);

				vc.vertices.push_back(v1);
				vc.vertices.push_back(v2);
				vc.vertices.push_back(v3);
				vc.vertices.push_back(v4);


				float b1 =  v1.z / max_height;
				float b2 = v2.z / max_height;
				float b3 = v3.z / max_height;
				float b4 = v4.z / max_height;

				vc.vertices_color.push_back(COLOR(b1, b1, b1, 1));
				vc.vertices_color.push_back(COLOR(b2, b2, b2, 1));
				vc.vertices_color.push_back(COLOR(b3, b3, b3, 1));
				vc.vertices_color.push_back(COLOR(b4, b4, b4, 1));

			}
		}

		Entity* e = Shape::GetRectangleShape(vc);
		int tempEntityIndex = GetRenderSystem()->addEntity(e);
		GetRenderSystem()->initEntityBuffers(tempEntityIndex);




}


