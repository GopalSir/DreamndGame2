#include "../../include/System/CrappyBirdSystem.h"

/*
* Systems hold refrences to Entities.. and go over the components they are intersted in
* each interation of the game engine and perform logic operation based on component state. 
* 
* Systems will also Emit Custom Game events. 
* 
* Design Decision: Where should HandleEvent() function lie? with Components or Systems.. solved : System
* 
*/

std::vector<Entity*> CrappyBirdSystem::GeneratePillar(int _r_limit, int y_limit, int _dir, int _width, int _height)
{

	float y_rand = 30 * ((float)rand() / RAND_MAX);
	float x_rand = 30 * ((float)rand() / RAND_MAX);

	float end_height = (float)_height / 10;

	DREAM::VerticesComponent<float> vc1;
	DREAM::VerticesComponent<float> vc2;
	
	if (_dir == 0)
	{
		vc1.vertices.push_back(PositionComponent<float>(_r_limit, y_limit , 0));
		vc1.vertices.push_back(PositionComponent<float>(_r_limit, y_limit+ _height + y_rand, 0));
		vc1.vertices.push_back(PositionComponent<float>(_r_limit + 20, y_limit +  _height + y_rand, 0));
		vc1.vertices.push_back(PositionComponent<float>(_r_limit + 20, y_limit , 0));


		vc2.vertices.push_back(PositionComponent<float>(_r_limit, y_limit + _height + y_rand - end_height, 0));
		vc2.vertices.push_back(PositionComponent<float>(_r_limit, y_limit + _height + y_rand, 0));
		vc2.vertices.push_back(PositionComponent<float>(_r_limit + 20, y_limit + _height + y_rand, 0));
		vc2.vertices.push_back(PositionComponent<float>(_r_limit+20, y_limit + _height + y_rand - end_height, 0));


	}
	else if (_dir == 1)
	{
		vc1.vertices.push_back(PositionComponent<float>(_r_limit, y_limit , 0));
		vc1.vertices.push_back(PositionComponent<float>(_r_limit, y_limit - _height - y_rand, 0));
		vc1.vertices.push_back(PositionComponent<float>(_r_limit + 20, y_limit - _height - y_rand, 0));
		vc1.vertices.push_back(PositionComponent<float>(_r_limit + 20, y_limit , 0));

		vc2.vertices.push_back(PositionComponent<float>(_r_limit, y_limit + _height + y_rand - end_height, 0));
		vc2.vertices.push_back(PositionComponent<float>(_r_limit, y_limit + _height + y_rand, 0));
		vc2.vertices.push_back(PositionComponent<float>(_r_limit + 20, y_limit + _height + y_rand, 0));
		vc2.vertices.push_back(PositionComponent<float>(_r_limit + 20, y_limit + _height + y_rand - end_height, 0));
	}

	

	Entity* pillarBody = Shape::GetRectangleShape(vc1);
	pillarBody->getComponent<DrawableComponent>()->color = COLOR(0, 255, 255, 1);

	Entity* pillarEnd = Shape::GetRectangleShape(vc2);
	pillarEnd->getComponent<DrawableComponent>()->color = COLOR(200, 0, 255, 1);

	return { pillarBody, pillarEnd };
	
}

void CrappyBirdSystem::CheckPillarCondition()
{

}

CrappyBirdSystem::CrappyBirdSystem()
{
	std::cout << "CrappyBirdSytemActive\n";


}

void CrappyBirdSystem::update()
{
	
	/*
	* Check for collition of bird entity with rest of the pillar entities
	*/
	for (auto* tempEntity : entities)
	{
		CrappyBirdComponent* crappyBirdComponent = tempEntity->getComponent<CrappyBirdComponent>();
		PhysicsComponent* physicsComponent = tempEntity->getComponent<PhysicsComponent>();
		PhysicsComponent* cameraPhysicsComponent = crappyBirdComponent->cameraPhysicsComponent;
		//std::cout << "updating crappy system";
		
		cameraPhysicsComponent->position.x = physicsComponent->position.x;
		cameraPhysicsComponent->position.y = physicsComponent->position.y;

		cameraPhysicsComponent->rotation.z += physicsComponent->velocity.y/2000;
		if (cameraPhysicsComponent->rotation.z >= 90)
		{
			cameraPhysicsComponent->rotation.z = 90;
		}

		if (physicsComponent->position.y <= 0)
		{
			//Game Over Event
			physicsComponent->position.y = 130;
			physicsComponent->velocity.y = 0;
		}

		//if (crappyBirdComponent->collided == true)
		//{
		//	//Game over event
		//}


		/*
		  check if we have moved 5 meters after genration of last pillar, if yes, generate new pillar
		  within a specified range at rhs of screen ( outside of play  area so that it's visible later)
		*/
		if ((physicsComponent->position.x - crappyBirdComponent->p_previous.x) > 100)
		{

			float  r_limit1 = physicsComponent->position.x + crappyBirdComponent->r_limit + 100 * (float(rand()) / RAND_MAX);
			float r_limit2 = physicsComponent->position.x + crappyBirdComponent->r_limit + 100 * (float(rand()) / RAND_MAX);

			std::cout << "Generating Piller\n";
			std::vector<Entity*> tempPillar1 = GeneratePillar(r_limit1, 0, 0, 25, 80);
			std::vector<Entity*>  tempPillar2 = GeneratePillar(r_limit2,400, 1, 25, 180);

			PhysicsComponent* pillar_pc = new PhysicsComponent();
			PhysicsComponent* pillar_pc2 = new PhysicsComponent();
			

			for (auto* e : tempPillar1)
			{
				e->addComponent(pillar_pc);
			}

			for (auto* e : tempPillar2)
			{
				e->addComponent(pillar_pc2);
			}

			for (auto* e : tempPillar1)
			{
				int temp_index = crappyBirdComponent->renderSystem->addEntity(e);
				crappyBirdComponent->renderSystem->initEntityBuffers(temp_index);
			}

			for (auto* e : tempPillar2)
			{
				int temp_index = crappyBirdComponent->renderSystem->addEntity(e);
				crappyBirdComponent->renderSystem->initEntityBuffers(temp_index);
			}

			//Now we generate the end portion of the pillar 

			crappyBirdComponent->p_previous = PositionComponent<float>(physicsComponent->position.x, physicsComponent->position.y, physicsComponent->position.z);

			
		}
	}
}

void CrappyBirdSystem::SetBirdEntityIndex(int _index)
{
	bird_entity_index = _index;
}
