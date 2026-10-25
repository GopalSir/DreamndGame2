#include "../../include/system/CollisionSystem.hpp"


void CollisionSystem::update()
{

	//For every registered entity
	for (auto *entity : entities)
	{
		//Get the physics component
		DREAM::PhysicsComponent *physics_component = entity->getComponent<DREAM::PhysicsComponent>();
		ColliderComponent *collidor_component = entity->getComponent<ColliderComponent>();
		if(physics_component == nullptr)
		{
			//std::cout<<"physicsComponent of this entity is nullptr"<<std::endl;
		}
		else if (collidor_component == nullptr)
		{
			//std::cout<<"CollidorComponent of this entity is nullptr"<<std::endl;

		}
		else
		{
			//std::cout<<"Checking for collision"<<std::endl;
			Mat4<float> model_matrix = DREAM::PhysicsSystem::GetModelMatrixfromComponent(physics_component);

			//Generate 8 cornrs of the unit cubbah
			for(int i=0;i<8;++i)
			{
			    float sx = (i & 1) ? 1.0f : -1.0f;
			    float sy = (i & 2) ? 1.0f : -1.0f;
			    float sz = (i & 4) ? 1.0f : -1.0f;	
			    
			    Vec3<float> he = collidor_component->half_extents;
			    Vec3<float> corner = Vec3<float>(sx*he.x ,sy*he.y ,sz*he.z);

			    Vec4<float> corner_world_pos = model_matrix*Vec4(corner.x,corner.y,corner.z,1.0f);
			    Vec3<float> corner_world_pos_v3 = Vec3<float>(corner_world_pos.x,
			    											corner_world_pos.y,
			    											corner_world_pos.z
			    												);
			    float  d = Vec3<float>::dot(corner_world_pos_v3,Vec3<float>(0,1,0)) - (-1);

			    //Collision Detected 
			    if(d<0)
			    {
			    	std::cout<<"collision"<<std::endl;
			    }
			}

		}
	}
}

void CollisionSystem::onEntityAddition(Entity* _entity)
{
	std::cout<<"Entity added to collision system"<<std::endl;
}
