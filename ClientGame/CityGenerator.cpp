#include "CityGenerator.h"


double rand01() {
	static std::random_device rd;                         // non-deterministic seed (if available)
	static std::mt19937 gen(rd());                        // mersenne twister engine (static so we don't reseed)
	static std::uniform_real_distribution<double> dist(0.0, 1.0); // range [0.0, 1.0)
	return dist(gen);
}


Entity* CityGenerator::GetCity()
{
	static int counter = 0;

	
	

	int city_x_blockCount = (float)city_x / city_to_world_resolution;
	int city_y_blockCount = (float)city_y / city_to_world_resolution;

	std::cout << "DEBUG: Grid size is " << city_x_blockCount << " wide by " << city_y_blockCount << " tall." << std::endl;


	std::vector<std::pair<int, int>> newRoads;

	std::vector<std::pair<int, int>>  newRoads2, newRoads2_copy;

	if (counter == 0)
	{
		for (auto kv : cityStatus)
		{
			newRoads.push_back(kv.first);
		}
	}

	newRoads2.clear();

	DREAM::VerticesComponent<float>* myVC = new DREAM::VerticesComponent<float>();
	

	for (int i = 0; i < mIterationCount; ++i)
	{
		newRoads2.clear();
		//Traverse existing roads, find the closest road coordinate and add a new road towards it. ( using simple vector addition)
		for (auto kv : newRoads)
		{
			//this loop only runs on coordinates which are roads. 

			ROAD_DIRECTION oldSourceRoadDirection = roadDirection[kv];

			auto nearestCoord = FindNearestRoad(kv, newRoads);
			auto newRoadCoord = MoveTowardsCoord(kv, nearestCoord);

			/*
			Sanity checks for newRoadCoord
			*/

			//Getting placed on an already placed block 
			if (cityStatus[newRoadCoord] == true)
			{
				//This means kv and newCoord need to connect, before newCoord is changed to a unoccupied cell
				//FixDirections(kv, newRoadCoord);

				newRoadCoord = FindAjdacentUnoccupied(newRoadCoord);

			}

			if (newRoadCoord.first >= city_x_blockCount || newRoadCoord.first < 0 || newRoadCoord.second >= city_y_blockCount || newRoadCoord.second < 0)
			{
				continue;
			}

			// Check if FindAdjacentUnoccupied returned invalid coords
			if (newRoadCoord.first == -1 || newRoadCoord.second == -1)
			{
				continue;
			}

			FixDirections(kv, newRoadCoord);

			//Now this city is being displayed frame by frame. We need to get new graphics based on the changed road direction 
			// of existing roads... yk. 

			cityStatus[newRoadCoord] = true;
			//GenerateRoad(newRoadCoord.first, newRoadCoord.second, myVC, COLOR(0, 0, 0, 1));
			//GenerateStrip(kv.first, kv.second, myVC, COLOR(0, 0, 0, 1), oldSourceRoadDirection);
			//std::cout <<  roadDirection[newRoadCoord];

			newRoads2.push_back(newRoadCoord);
		}
		newRoads = newRoads2;
	}

	//Generate all Vertices at once. 
	



	for (auto p : cityStatus)
	{
		if (p.second == true)
		{
			if (initialBlocks[std::make_pair(p.first.first, p.first.second)] == true)
			{
				GenerateRoad(p.first.first, p.first.second, myVC, COLOR(0, 1, 0, 1));
			}
			else
			{
				GenerateRoad(p.first.first, p.first.second, myVC, COLOR(0, 0, 0, 1));
			}
		}
	}

	std::cout << "Size of cities vertices: " << myVC->vertices.size();

	Entity* roads = Shape::GetRectangleShape(*myVC);

	counter++;

	return roads;

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

		r = lua_getglobal(mlua_State, "road_strip_width_percentage");
		if (r == LUA_TNUMBER)
		{
			road_strip_width_percentage = lua_tonumber(mlua_State, -1);
			lua_pop(mlua_State, 1);
		}


	}

	std::cout << city_to_world_resolution;

	int city_x_blockCount = (float)city_x / city_to_world_resolution;
	int city_y_blockCount = (float)city_y / city_to_world_resolution;

	std::cout << "DEBUG: Grid size is " << city_x_blockCount << " wide by " << city_y_blockCount << " tall." << std::endl;


	int num_road_seed = 2;

	if (num_road_seed > 100)
	{
		num_road_seed = 100;
	}

	// //Draw all brown square for bird initially
	for (int i = 0; i < city_x_blockCount; ++i)
	{
		for (int j = 0; j < city_y_blockCount; ++j)
		{
			if (rand01() < mgenerationProbability)
			{
				//std::cout << "Generating City block" << i << " " << j << "\n";
				/*GenerateRoad(i, j);*/
				auto pair = std::make_pair(i, j);
				cityStatus[pair] = 1;
				roadDirection[pair] = ROAD_DIRECTION::EAST;
				initialBlocks[pair] = true;
			}

		}
	}


}



void CityGenerator::DrawBounds()
{
	

	DREAM::VerticesComponent<float>* myVC = new DREAM::VerticesComponent<float>();

	myVC->vertices.push_back(PositionComponent<float>(0, 0, 0));
	myVC->vertices_color.push_back(COLOR(1, 1, 1, 1));

	myVC->vertices.push_back(PositionComponent<float>(0, 500, 0));
	myVC->vertices_color.push_back(COLOR(1, 1, 1, 1));

	myVC->vertices.push_back(PositionComponent<float>(500, 500, 0));
	myVC->vertices_color.push_back(COLOR(1, 1, 1, 1));

	myVC->vertices.push_back(PositionComponent<float>(500, 0, 0));
	myVC->vertices_color.push_back(COLOR(1, 1, 1, 1));

	Entity* a = Shape::GetRectangleShape(*myVC);
	city.push_back(a);
}

void CityGenerator::PaintInitialBlocks(DREAM::VerticesComponent<float>* _vc)
{
	for (auto p : initialBlocks)
	{
		int i = p.first.first;
		int j = p.first.second;



		// Road base (black rectangle)
		_vc->vertices.push_back(PositionComponent<float>((i * city_to_world_resolution), j * city_to_world_resolution, 0));
		_vc->vertices_color.push_back(COLOR(0, 1, 0, 1));

		_vc->vertices.push_back(PositionComponent<float>((i * city_to_world_resolution), j * city_to_world_resolution + city_to_world_resolution, 0));
		_vc->vertices_color.push_back(COLOR(0, 1, 0, 1));

		_vc->vertices.push_back(PositionComponent<float>((i * city_to_world_resolution) + city_to_world_resolution, j * city_to_world_resolution + city_to_world_resolution, 0));
		_vc->vertices_color.push_back(COLOR(0, 1, 0, 1));

		_vc->vertices.push_back(PositionComponent<float>((i * city_to_world_resolution) + city_to_world_resolution, j * city_to_world_resolution, 0));
		_vc->vertices_color.push_back(COLOR(0, 1, 0, 1));
	}
}

void CityGenerator::GenerateStrip(int i, int j, DREAM::VerticesComponent<float>* _vc, COLOR _color,ROAD_DIRECTION _oldRD)
{
	// Add white strip in the middle (10% of the length)
	float stripWidth = city_to_world_resolution * road_strip_width_percentage / 100;  // 10% of road width
	float stripOffset = (city_to_world_resolution - stripWidth) / 2.0f;  // Center the strip

	float baseX = i * city_to_world_resolution;
	float baseY = j * city_to_world_resolution;
	float centerX = baseX + city_to_world_resolution / 2.0f;
	float centerY = baseY + city_to_world_resolution / 2.0f;

	int rd = roadDirection[std::make_pair(i, j)] ^ _oldRD;

	// Draw strips based on bitwise flags
	if (rd & ROAD_DIRECTION::NORTH)
	{
		// Strip from bottom to center (vertical)
		_vc->vertices.push_back(PositionComponent<float>(centerX - stripWidth / 2, baseY, 0.1));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(centerX - stripWidth / 2, centerY, 0.1));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(centerX + stripWidth / 2, centerY, 0.1));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(centerX + stripWidth / 2, baseY, 0.1));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White
	}

	if (rd & ROAD_DIRECTION::SOUTH)
	{
		// Strip from center to top (vertical)
		_vc->vertices.push_back(PositionComponent<float>(centerX - stripWidth / 2, centerY, 0.1));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(centerX - stripWidth / 2, baseY + city_to_world_resolution, 0.1));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(centerX + stripWidth / 2, baseY + city_to_world_resolution, 0.1));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(centerX + stripWidth / 2, centerY, 0.1));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White
	}

	if (rd & ROAD_DIRECTION::EAST)
	{
		// Strip from left wall to center (horizontal)
		_vc->vertices.push_back(PositionComponent<float>(baseX, centerY - stripWidth / 2, 0.1));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(baseX, centerY + stripWidth / 2, 0.1));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(centerX, centerY + stripWidth / 2, 0.1));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(centerX, centerY - stripWidth / 2, 0.1));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White
	}

	if (rd & ROAD_DIRECTION::WEST)
	{
		// Strip from center to right wall (horizontal)
		_vc->vertices.push_back(PositionComponent<float>(centerX, centerY - stripWidth / 2, 0.1));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(centerX, centerY + stripWidth / 2, 0.1));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(baseX + city_to_world_resolution, centerY + stripWidth / 2, 0.1));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(baseX + city_to_world_resolution, centerY - stripWidth / 2, 0.1));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White
	}
}


void CityGenerator::GenerateRoad(int i, int j, DREAM::VerticesComponent<float>* _vc,COLOR _color)
{
	// Add white strip in the middle (10% of the length)
	float stripWidth = city_to_world_resolution * road_strip_width_percentage / 100;  // 10% of road width
	float stripOffset = (city_to_world_resolution - stripWidth) / 2.0f;  // Center the strip

	float baseX = i * city_to_world_resolution;
	float baseY = j * city_to_world_resolution;
	float centerX = baseX + city_to_world_resolution / 2.0f;
	float centerY = baseY + city_to_world_resolution / 2.0f;

	ROAD_DIRECTION rd = roadDirection[std::make_pair(i, j)];

	// Draw strips based on bitwise flags
	if (rd & ROAD_DIRECTION::NORTH)
	{
		// Strip from bottom to center (vertical)
		_vc->vertices.push_back(PositionComponent<float>(centerX - stripWidth / 2, baseY, 0));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(centerX - stripWidth / 2, centerY, 0));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(centerX + stripWidth / 2, centerY, 0));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(centerX + stripWidth / 2, baseY, 0));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White
	}

	if (rd & ROAD_DIRECTION::SOUTH)
	{
		// Strip from center to top (vertical)
		_vc->vertices.push_back(PositionComponent<float>(centerX - stripWidth / 2, centerY, 0));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(centerX - stripWidth / 2, baseY + city_to_world_resolution, 0));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(centerX + stripWidth / 2, baseY + city_to_world_resolution, 0));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(centerX + stripWidth / 2, centerY, 0));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White
	}

	if (rd & ROAD_DIRECTION::EAST)
	{
		// Strip from left wall to center (horizontal)
		_vc->vertices.push_back(PositionComponent<float>(baseX, centerY - stripWidth / 2, 0));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(baseX, centerY + stripWidth / 2, 0));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(centerX, centerY + stripWidth / 2, 0));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(centerX, centerY - stripWidth / 2, 0));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White
	}

	if (rd & ROAD_DIRECTION::WEST)
	{
		// Strip from center to right wall (horizontal)
		_vc->vertices.push_back(PositionComponent<float>(centerX, centerY - stripWidth / 2, 0));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(centerX, centerY + stripWidth / 2, 0));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(baseX + city_to_world_resolution, centerY + stripWidth / 2, 0));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White

		_vc->vertices.push_back(PositionComponent<float>(baseX + city_to_world_resolution, centerY - stripWidth / 2, 0));
		_vc->vertices_color.push_back(COLOR(1, 1, 1, 1));  // White
	}

	// Road base (black rectangle)
	_vc->vertices.push_back(PositionComponent<float>((i * city_to_world_resolution), j * city_to_world_resolution, 0));
	_vc->vertices_color.push_back(_color);

	_vc->vertices.push_back(PositionComponent<float>((i * city_to_world_resolution), j * city_to_world_resolution + city_to_world_resolution, 0));
	_vc->vertices_color.push_back(_color);

	_vc->vertices.push_back(PositionComponent<float>((i * city_to_world_resolution) + city_to_world_resolution, j * city_to_world_resolution + city_to_world_resolution, 0));
	_vc->vertices_color.push_back(_color);

	_vc->vertices.push_back(PositionComponent<float>((i * city_to_world_resolution) + city_to_world_resolution, j * city_to_world_resolution, 0));
	_vc->vertices_color.push_back(_color);
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
	ROAD_DIRECTION target_direction;

	if (abs(_currentRoad.first - _targetRoad.first) >= (_currentRoad.second - _targetRoad.second))
	{
		if ((_currentRoad.first - _targetRoad.first) < 0) // Target is to the right
		{
			result.first = _currentRoad.first + 1;

			//result's direction will be EAST
			target_direction = ROAD_DIRECTION::EAST;

		}
		else if ((_currentRoad.first - _targetRoad.first) > 0)  // Target is on the left
		{
			result.first = _currentRoad.first - 1;
			//result's direction will be WEST
			target_direction = ROAD_DIRECTION::WEST;
		}
		else
		{
			result.first = _currentRoad.first;

			//result's direction will be SAME AS THAT OF TARGET
			target_direction = roadDirection[_currentRoad];

		}
		result.second = _currentRoad.second;
		//roadDirection[result] = target_direction;
	}
	else {
		if ((_currentRoad.second - _targetRoad.second) < 0) // Target is to the top
		{
			result.second = _currentRoad.second + 1;

			//result's direction will be NORTH
			target_direction = ROAD_DIRECTION::NORTH;
		}
		else if ((_currentRoad.second - _targetRoad.second) > 0)  // Target is on the bottom
		{
			result.second = _currentRoad.second - 1;

			//result's direction will be SOUTH
			target_direction = ROAD_DIRECTION::SOUTH;
		}
		else
		{
			result.second = _currentRoad.second;

			//result's direction will be SAME AS THAT OF TARGET
			target_direction = roadDirection[_currentRoad];

		}
		result.first = _currentRoad.first;
		//roadDirection[result] = target_direction;
	}
	return result;

}

// This is the main logic you requested.
// It finds a random, unoccupied neighbor that is NOT touched by 2 or more sides.
std::pair<int, int> CityGenerator::FindAjdacentUnoccupied(std::pair<int, int> _currentRoad)
{
	// Define the master list of offsets as a constant.
	static const std::vector<std::pair<int, int>> eight_direction_offsets = {
		{ 0,  1},  { 1,  0}, 
		{ 0, -1}, {-1,  0}, 
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

//Take target and current road block, change direction of current block to match the directio of target block.
//This can only add direction, cannot take away old direction. 
void CityGenerator::FixDirections(std::pair<int, int> _c1, std::pair<int, int> _c2)
{
	//if _c1 and _c2 guaranteed to be adjacent, now
	/*
	if _c1 is to the left of _c2, add WEST to _c1's direction
	if _c1 is to the right of _c2, add EAST to _c1's direction
	if _c1 is to the top of _c2, add NORTH to _c1's direction
	if _c1 is to the bottom of _c2, add SOUTH to _c1's direction
	*/
	ROAD_DIRECTION current = roadDirection[_c1];

	if (_c1.first < _c2.first)
		// _c1 is to the left of _c2, add WEST to _c1's direction
	{
		roadDirection[_c1] = static_cast<ROAD_DIRECTION>(current | ROAD_DIRECTION::WEST);
		roadDirection[_c2] = static_cast<ROAD_DIRECTION>(roadDirection[_c2] | ROAD_DIRECTION::EAST);
	}
	else if (_c1.first > _c2.first)
	{
		// _c1 is to the right of _c2, add EAST to _c1's direction
		roadDirection[_c1] = static_cast<ROAD_DIRECTION>(current | ROAD_DIRECTION::EAST);
		roadDirection[_c2] = static_cast<ROAD_DIRECTION>(roadDirection[_c2] | ROAD_DIRECTION::WEST);
	}
	else if (_c1.second < _c2.second)
	{
		// _c1 is to the bottom of _c2, add SOUTH to _c1's direction
		roadDirection[_c1] = static_cast<ROAD_DIRECTION>(current | ROAD_DIRECTION::SOUTH);
		roadDirection[_c2] = static_cast<ROAD_DIRECTION>(roadDirection[_c2] | ROAD_DIRECTION::NORTH);
	}
	else if (_c1.second > _c2.second)
	{
		// _c1 is to the top of _c2, add NORTH to _c1's direction
		roadDirection[_c1] = static_cast<ROAD_DIRECTION>(current | ROAD_DIRECTION::NORTH);
		roadDirection[_c2] = static_cast<ROAD_DIRECTION>(roadDirection[_c2] | ROAD_DIRECTION::SOUTH);
	}
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




