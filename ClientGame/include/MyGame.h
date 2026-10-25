#pragma once
#include <System/MyApplication.hpp>
#include <EVENTS.hpp>
#include "../include/Component/ThrusterComponenet.hpp"
#include <Shape.hpp>
#include "../include/Component/CameraControllerComponent.h"
#include "../include/Component/JointComponent.h"
#include "../include/Component/LinkComponent.h"
#include "../include/system/PlayerSystem.hpp"
#include <System/CollisionSystem.hpp>



class MyGame : public DREAM::MyApplication
{
	Shader* basicShader;
	void setupShaders();
	void setupEntities();
	void setupFloorEntity();
public: 
	
	MyGame();
};

