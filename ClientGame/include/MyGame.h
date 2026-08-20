#pragma once
#include <System/MyApplication.hpp>
#include <EVENTS.hpp>
#include "../include/Component/ThrusterComponenet.hpp"
#include <Shape.hpp>
#include "../include/Component/CameraControllerComponent.h"



class MyGame : public DREAM::MyApplication
{
	Shader* basicShader;
	void setupShaders();
	void setupEntities();
public: 
	
	MyGame();
};

