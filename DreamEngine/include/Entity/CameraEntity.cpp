#include "CameraEntity.hpp"

CameraEntity::CameraEntity(PhysicsComponent* _physicsComponent, MVPComponent* _mvpComponent)
{
	this->addComponent(_physicsComponent);
	this->addComponent(_mvpComponent);
}
