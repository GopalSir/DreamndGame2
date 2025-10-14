#pragma once
#include <System/MyApplication.hpp>
#include <EVENTS.hpp>
#include "../include/Component/ThrusterComponenet.hpp"
#include <Shape.hpp>
#include "../include/Component/CameraControllerComponent.h"
#include "ShapeCreator.hpp"
#include "../include/System/CrappyBirdSystem.h"
#include "../CitySystem.h"

class MyGame : public DREAM::MyApplication
{
public: 
	ShapeCreator* _shapeCreator;
	MyGame();
	//void GenerateRectangle();

	//void run() override;

	




};

