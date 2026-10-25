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
		MyApplication::addGameSystem(new DREAM::CollisionSystem());


		setupEntities();
		setupFloorEntity();


		

}

void MyGame::setupShaders(){
	
	//Set up shaders for the program
	basicShader = new Shader("shaders/BasicVertexShader.glsl", "shaders/BasicFragmentShader.glsl");
	basicShader->use();
	// Off-axis rather than straight overhead - a light directly above leaves
	// every side face at zero diffuse, so the cube reads as a flat blob.
	basicShader->setUniform(basicShader->programID, "light_position", 25.0f, 35.0f, 40.0f, 1.0f);
	// The fragment shader multiplies its ambient term by this. Leave it unset
	// and it defaults to 0, which kills ambient entirely and only the faces
	// aimed at the light light up at all.
	basicShader->setUniform(basicShader->programID, "ambient_light", 0.45f, 0.45f, 0.45f, 1.0f);
		


    
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

	cubeEntity->addComponent(new DREAM::PhysicsComponent(Vec4<float>(0.0f, 0.0f, 0.0f, 0.0f),   // velocity
															Vec4<float>(0.0f, 14.0f, 0.0f, 1.0f),  // position
															Vec4<float>(18.0f, 0.0f, 24.0f, 0.0f), // rotation - tilted so it lands on a corner
															Vec4<float>(0.0f, 0.0f, 0.0f, 0.0f),   // rotation_velocity
															true));                                 // isGravity
	cubeEntity->addComponent(new DREAM::ColliderComponent(
		DREAM::ColliderType::BOX,
		Vec3<float>(1,1,1),
		Vec3<float>(0,1,0),
		0.0f));

	// Rotational counterpart of mass. For a cube: (2/3) * mass * half_extent^2
	// Leave it at the default 1.0 and a big cube spins far too fast.
	DREAM::PhysicsComponent* cubePhysics = cubeEntity->getComponent<DREAM::PhysicsComponent>();
	cubePhysics->mass    = 1.0f;
	cubePhysics->inertia = (2.0f / 3.0f) * cubePhysics->mass * 1.0f * 1.0f;

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




