#include "CityGenerator.h"


double rand01() {
	static std::random_device rd;                         // non-deterministic seed (if available)
	static std::mt19937 gen(rd());                        // mersenne twister engine (static so we don't reseed)
	static std::uniform_real_distribution<double> dist(0.0, 1.0); // range [0.0, 1.0)
	return dist(gen);
}


std::vector<Entity*> CityGenerator::GetCity()
{

	return city;

}

CityGenerator::CityGenerator()
{
	/*
	* Definitoin for roads: they will be places randomly at first, and then grow towards each other.  
	*/
	city_to_world_resolution = 10.0f;
	city_x = 200;
	city_y = 200;


	int num_road_seed = city_x / 3;
	
	if (num_road_seed > 10)
	{
		num_road_seed = 10;
	}

	// Draw all brown square for bird initially
	for (int i = 0; i < city_x; ++i)
	{
		for (int j = 0; j< city_y; ++j)
		{
			if (rand01() <0.006f)
			{
				//std::cout << "Generating City block" << i << " " << j << "\n";
				GenerateRoad(i, j);
				auto pair = std::make_pair(i, j);
				cityStatus[pair] = 1;
			}
			
		}
	}

	std::vector<std::pair<int, int>> newRoads, newRoads2, newRoads2_copy;
	for (auto kv : cityStatus)
	{
		newRoads.push_back(kv.first);
	}

	newRoads2.clear();

	for (int k = 0; k < 50; ++k)
	{
		

		newRoads2.clear();
		//Traverse existing roads, find the closest road coordinate and add a new road towards it. ( using simple vector addition)
		for (auto kv : newRoads)
		{
			//this loop only runs on coordinates which are roads. 

			auto nearestCoord = FindNearestRoad(kv, newRoads);
			auto newRoadCoord = MoveTowardsCoord(kv,nearestCoord);
			GenerateRoad(newRoadCoord.first, newRoadCoord.second);
			cityStatus[newRoadCoord] = true;

			newRoads2.push_back(newRoadCoord);
		}
		newRoads = newRoads2;
	}

}



void CityGenerator::GenerateRoad(int i, int j)
{
	DREAM::VerticesComponent<float> vc;
	vc.vertices.push_back(PositionComponent<float>((i* city_to_world_resolution), j* city_to_world_resolution, 0));
	vc.vertices.push_back(PositionComponent<float>((i * city_to_world_resolution), j * city_to_world_resolution+10, 0));
	vc.vertices.push_back(PositionComponent<float>((i * city_to_world_resolution) +10, j * city_to_world_resolution+10, 0));
	vc.vertices.push_back(PositionComponent<float>((i * city_to_world_resolution) + 10, j * city_to_world_resolution, 0));

	Entity* roadBlock = Shape::GetRectangleShape(vc);

	roadBlock->getComponent<DrawableComponent>()->color = COLOR(165, 42, 42,1.0f);
	
	city.push_back(roadBlock);
}

std::pair<int,int> CityGenerator::FindNearestRoad(std::pair<int, int> _roadCoord, std::vector< std::pair<int, int>>_blockList)
{
	int shortestDistance = INT_MAX;
	std::pair<int, int> result;

	if (cityStatus.size() <= 1)
	{
		Log::LogMessage("Not possible to find nearest neighbor in current state of city");
	}
	for (auto kv : _blockList)
	{
		int distance = ManhattanDistance(_roadCoord, kv);
		if (distance < shortestDistance && _roadCoord != kv)
		{
			shortestDistance = distance;
			result = kv;
		}
	}

	return result;
}

std::pair<int, int> CityGenerator::MoveTowardsCoord(std::pair<int, int> _currentRoad, std::pair<int, int> _targetRoad)
{
	std::pair<int, int> result;
	if ((_currentRoad.first - _targetRoad.first) < 0) // Target is to the right
	{
		result.first = _currentRoad.first + 1;
	}
	else if ((_currentRoad.first - _targetRoad.first) > 0)  // Target is on the left
	{
		result.first = _currentRoad.first - 1;
	}
	else
	{
		result.first = _currentRoad.first;
	}
		
	if ((_currentRoad.second - _targetRoad.second) < 0) // Target is to the bottom
	{
		result.second = _currentRoad.second - 1;
	}
	else if ((_currentRoad.second - _targetRoad.second) > 0)  // Target is on the left
	{
		result.second = _currentRoad.second + 1;
	}
	else
	{
		result.second = _currentRoad.second;
	}

	return result;

}

int CityGenerator::ManhattanDistance(std::pair<int, int> _c1, std::pair<int, int> _c2)
{
	return (abs(_c1.first - _c2.first) + abs(_c1.second - _c2.second));
}




