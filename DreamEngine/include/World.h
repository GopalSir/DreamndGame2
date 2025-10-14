#pragma once
#include <ECS_Core/Core.hpp>
#include <System/RenderSystem.hpp>
#include <System/PhysicsSystem.h>
#include <System/CameraSystem.hpp>

namespace DREAM {
	class World
	{
	public:
		 RenderSystem* renderSystem;
		PhysicsSystem* physicsSystem;
		 CameraSystem* cameraSystem;

	
		World(RenderSystem* _renderSystem, PhysicsSystem* _physicsSystem, CameraSystem* _cameraSystem)
		{
			renderSystem = _renderSystem;
			physicsSystem = _physicsSystem;
			cameraSystem = _cameraSystem;
		}
	};

}

