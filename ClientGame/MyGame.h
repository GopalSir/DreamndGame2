#pragma once
#include <System/MyApplication.hpp>
#include <EVENTS.hpp>
#include "ThrusterComponenet.hpp"
#include "Shape.hpp"
#include "CameraControllerComponent.h"
#include "ShapeCreator.hpp"

class MyGame : public DREAM::MyApplication
{
public: 
	ShapeCreator* _shapeCreator;
	MyGame();
	//void GenerateRectangle();

	//void run() override;




};

