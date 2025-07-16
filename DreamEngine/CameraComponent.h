#pragma once
#include <ECS_Core/Component.hpp>
#include <IEventHandler.hpp>

namespace DREAM
{
	class CameraComponent : public Component, public IEventHandler
	{
	public:
		float field_of_view;


		CameraComponent() = default;
	};
}

