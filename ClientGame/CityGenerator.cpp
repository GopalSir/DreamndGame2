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

	mlua_State = luaL_newstate();
	luaL_openlibs(mlua_State);

	int result = luaL_dofile(mlua_State, "config.lua");
	if (result != LUA_OK) {
		std::cout << "LUA ERROR: " << lua_tostring(mlua_State, -1) << std::endl;
		lua_pop(mlua_State, 1);
	}
	else {
		std::cout << "LUA FILE LOADED SUCCESSFULLY" << std::endl;
	
	

		std::cout << "LUA OK LOADING CONFIG NOW\n";

		// After loading the file, add this debug code:
		lua_pushglobaltable(mlua_State);
		lua_pushnil(mlua_State);
		while (lua_next(mlua_State, -2) != 0) {
			if (lua_isstring(mlua_State, -2)) {
				std::cout << "Global: " << lua_tostring(mlua_State, -2) << std::endl;
			}
			lua_pop(mlua_State, 1);
		}
		lua_pop(mlua_State, 1);


		int	r = lua_getglobal(mlua_State, "city_to_world_resolution");
		
		if (r == LUA_TNUMBER)
		{
			city_to_world_resolution = lua_tonumber(mlua_State, -1);
			lua_pop(mlua_State, 1);
		}

		r = lua_getglobal(mlua_State, "city_x");
		if (r == LUA_TNUMBER)
		{
			city_x = lua_tonumber(mlua_State, -1);
			lua_pop(mlua_State, 1);
		}

		r = lua_getglobal(mlua_State, "city_y");
		if (r == LUA_TNUMBER)
		{
			city_y = lua_tonumber(mlua_State, -1);
			lua_pop(mlua_State, 1);
		}

		r = lua_getglobal(mlua_State, "IterationCount");
		if (r == LUA_TNUMBER)
		{
			mIterationCount = lua_tonumber(mlua_State, -1);
			lua_pop(mlua_State, 1);
		}

		r = lua_getglobal(mlua_State, "generationProbability");
		if (r == LUA_TNUMBER)
		{
			mgenerationProbability = lua_tonumber(mlua_State, -1);
			lua_pop(mlua_State, 1);
		}


	}

	std::cout << city_to_world_resolution;



	//city_to_world_resolution = 1;
	//city_x = 500;
	//city_y = 500;

	int city_x_blockCount = (float)city_x / city_to_world_resolution;
	int city_y_blockCount = (float)city_y / city_to_world_resolution;

	int num_road_seed = 2;
	
	if (num_road_seed > 100)
	{
		num_road_seed = 100;
	}

	// Draw all brown square for bird initially
	for (int i = 0; i < city_x_blockCount; ++i)
	{
		for (int j = 0; j< city_y_blockCount; ++j)
		{
			if (rand01() < mgenerationProbability)
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

	for (int k = 0; k < mIterationCount; ++k)
	{
		

		newRoads2.clear();
		//Traverse existing roads, find the closest road coordinate and add a new road towards it. ( using simple vector addition)
		for (auto kv : newRoads)
		{
			//this loop only runs on coordinates which are roads. 

			auto nearestCoord = FindNearestRoad(kv, newRoads);
			auto newRoadCoord = MoveTowardsCoord(kv,nearestCoord);

			/*
			Sanity checks for newRoadCoord
			*/

			//Getting placed on an already placed block 
			if (cityStatus[newRoadCoord] == true)
			{
				
				newRoadCoord = FindAjdacentUnoccupied(newRoadCoord);
				
			}

			if (newRoadCoord.first > city_x || newRoadCoord.first < 0 || newRoadCoord.second > city_y || newRoadCoord.second < 0)
			{
				continue;
			}


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
	vc.vertices.push_back(PositionComponent<float>((i * city_to_world_resolution), j * city_to_world_resolution+ city_to_world_resolution, 0));
	vc.vertices.push_back(PositionComponent<float>((i * city_to_world_resolution) + city_to_world_resolution, j * city_to_world_resolution+ city_to_world_resolution, 0));
	vc.vertices.push_back(PositionComponent<float>((i * city_to_world_resolution) + city_to_world_resolution, j * city_to_world_resolution, 0));

	Entity* roadBlock = Shape::GetRectangleShape(vc);

	roadBlock->getComponent<DrawableComponent>()->color = COLOR(0, 100, 42,1.0f);
	
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


	if (abs(_currentRoad.first - _targetRoad.first) >= (_currentRoad.second - _targetRoad.second))
	{
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
		result.second = _currentRoad.second;
	}
	else {
		if ((_currentRoad.second - _targetRoad.second) < 0) // Target is to the top
		{
			result.second = _currentRoad.second + 1;
		}
		else if ((_currentRoad.second - _targetRoad.second) > 0)  // Target is on the bottom
		{
			result.second = _currentRoad.second - 1;
		}
		else
		{
			result.second = _currentRoad.second;
		}
		result.first = _currentRoad.first;
	}
	return result;

}

// This is the main logic you requested.
// It finds a random, unoccupied neighbor that is NOT touched by 2 or more sides.
std::pair<int, int> CityGenerator::FindAjdacentUnoccupied(std::pair<int, int> _currentRoad)
{
	// Define the master list of offsets as a constant.
	static const std::vector<std::pair<int, int>> eight_direction_offsets = {
		{ 0,  1}, { 1,  1}, { 1,  0}, { 1, -1},
		{ 0, -1}, {-1, -1}, {-1,  0}, {-1,  1}
	};

	// 1. Create a temporary, non-const copy that we can shuffle.
	auto shuffled_directions = eight_direction_offsets;
	static std::random_device rd;
	static std::mt19937 g(rd());
	std::shuffle(shuffled_directions.begin(), shuffled_directions.end(), g);

	// Loop through the randomized directions to find a valid spot.
	for (const auto& offset : shuffled_directions)
	{
		// Calculate the potential new coordinate.
		std::pair<int, int> potential_coord = {
			_currentRoad.first + offset.first,
			_currentRoad.second + offset.second
		};

		// First, check if the spot is unoccupied.
		if (cityStatus.count(potential_coord) == 0 || cityStatus.at(potential_coord) == false)
		{
			// 2. If it is unoccupied, THEN check if it's crowded.
			//    This is your "touched by 2 sides" rule.
			if (CountRoadNeighbors(potential_coord) < 2)
			{
				// 3. This is a good spot! Return the full coordinate, not the offset.
				return potential_coord;
			}
		}
	}

	// If no suitable spot was found after checking all directions, return an invalid coordinate.
	return { -1, -1 };
}

int CityGenerator::ManhattanDistance(std::pair<int, int> _c1, std::pair<int, int> _c2)
{
	return (abs(_c1.first - _c2.first) + abs(_c1.second - _c2.second));
}

float CityGenerator::EuclideanDistance(std::pair<int, int> _c1, std::pair<int, int> _c2)
{
	return (sqrt((_c1.first - _c2.first) * (_c1.first - _c2.first) + (_c1.second - _c2.second) * (_c1.second - _c2.second)));
}

//Given two blocks, fill a triangle between them depending on where the c2 is. 
void CityGenerator::FillTriangleBetweenBlock(std::pair<int, int> _c1, std::pair<int, int> _c2)
{
}

// Helper function to count how many of a cell's 4 cardinal neighbors are roads.
int CityGenerator::CountRoadNeighbors(std::pair<int, int> _coord)
{
	int count = 0;

	// Define the 4 cardinal directions to check.
	static const std::vector<std::pair<int, int>> four_direction_offsets = {
		{ 0,  1}, // Top
		{ 1,  0}, // Right
		{ 0, -1}, // Bottom
		{-1,  0}  // Left
	};

	for (const auto& offset : four_direction_offsets)
	{
		std::pair<int, int> neighbor_coord = {
			_coord.first + offset.first,
			_coord.second + offset.second
		};

		// Use .count() and .at() for safe map access to check if a road exists.
		if (cityStatus.count(neighbor_coord) && cityStatus.at(neighbor_coord) == true)
		{
			count++;
		}
	}
	return count;
}




