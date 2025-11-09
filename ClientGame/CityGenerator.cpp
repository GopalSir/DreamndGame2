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



	DREAM::VerticesComponent<float>* myVC = new DREAM::VerticesComponent<float>();
	
	if (counter == 0)
	{
		InitializeAgents();

	}

	for (int i = 0; i < mIterationCount; ++i)
	{
		//Update all agents
		for (auto& agent : mAgents)
		{
			UpdateAgent(agent);
		}


		//Remove Dead Agents
		mAgents.erase(std::remove_if(mAgents.begin(), mAgents.end(),
			[](const RoadAgent& a) {return !a.alive; }),
			mAgents.end());

		//std::cout << "Iteration " << i << ": " << mAgents.size() << " agents alive" << std::endl;

		//Stop if no more agents
		if (mAgents.empty())
		{
			std::cout << "All agents Finished" << std::endl;
			break;
		}
	}


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


void CityGenerator::InitializeAgents()
{
	for (auto kv : initialBlocks)
	{
		int gridX = kv.first.first;
		int gridY = kv.first.second;

		//Create 2-4 agents per seed road
		int numAgents = 2 + (rand01() * 2);

		for (int i = 0; i < numAgents; ++i)
		{
			//Convert grid to world position
			float worldX = gridX + 0.5f;
			float worldY = gridY + 0.5f;

			//Random initial direction
			float angle = rand01() * 2.0f * 3.14159f;
			float vx = cos(angle);
			float vy = sin(angle);

			mAgents.push_back(RoadAgent(worldX, worldY, vx, vy));
			//std::cout << "Spwaned agent at(" << worldX << " ," << worldY << ")" << std::endl;
		}
	}
	std::cout << "Initialized " << mAgents.size() << " agents" << std::endl;
}

void CityGenerator::UpdateAgent(RoadAgent& _agent)
{
	if (!_agent.alive) return;

	_agent.age++;

	if (_agent.age > mMaxAgentAge)
	{
		_agent.alive = false;
		std::cout << "Agent died of Old age" << std::endl;
		return;
	}

	//Get current grid position
	int currentX = (int)_agent.position.x;
	int currentY = (int)_agent.position.y;

	//Check bounds
	int city_x_blockCount = (float)city_x / city_to_world_resolution;
	int city_y_blockCount = (float)city_y / city_to_world_resolution;

	if (currentX < 0 || currentX >= city_x_blockCount || currentY < 0 || currentY >= city_y_blockCount)
	{
		_agent.alive = false;
		std::cout << "Agent hit boudnary" << std::endl;
		return;
	}

	//Check if we hit an existing road
	if (cityStatus[{currentX, currentY}] == true)
	{
		//Success! solidify our trail
		SolidifyAgentTrail(_agent);

		//MaybeSpawn new agents
		if (rand01() < mSpawnChance)
		{
			SpawnAgentFromRoad(currentX, currentY);
		}

		_agent.alive = false;
		std::cout << "Agent connected to road!" << std::endl;
		return;
	}
	auto bestDir = GetBestDirection(_agent);

	//Apply momentum - blend old direction with new
	float newVx = _agent.velocity.x * mAgentMomentum + bestDir.first * (1.0f - mAgentMomentum);
	float newVy = _agent.velocity.y * mAgentMomentum + bestDir.second * (1.0f - mAgentMomentum);

	//Normalize Velocity
	float length = sqrt(newVx * newVx + newVy * newVy);
	if (length > 0.001f)
	{
		_agent.velocity.x = newVx / length;
		_agent.velocity.y = newVy / length;
	}

	//Move Agent
	_agent.position.x += _agent.velocity.x;
	_agent.position.y += _agent.velocity.y;

	//Record trail
	int newX = (int)_agent.position.x;
	int newY = (int)_agent.position.y;

	//Old add if we moved to a new cell 
	if (_agent.trail.empty() || _agent.trail.back() != std::make_pair(newX, newY))
	{
		_agent.trail.push_back({ newX,newY });
		mTrailStrength[{newX, newY}] += 1.0f;
	}

}

std::pair<float, float> CityGenerator::GetBestDirection(const RoadAgent& _agent)
{
	//Look at least 3 directions: left, forward, right
	std::vector<std::pair<float, float>> candidates;

	//Forward direction ( continue momentum) 
	candidates.push_back({ _agent.velocity.x, _agent.velocity.y });

	float leftVx = _agent.velocity.x * 0.707f - _agent.velocity.y * 0.707f;
	float leftVy = _agent.velocity.x * 0.707f + _agent.velocity.y * 0.707f;

	candidates.push_back({ leftVx,leftVy });

	float rightVx =  _agent.velocity.x * 0.707f + _agent.velocity.y * 0.707f;
	float rightVy = -_agent.velocity.x * 0.707f + _agent.velocity.y * 0.707f;
	candidates.push_back({ rightVx,rightVy });

	float bestScore = -999999.0f;
	std::pair<float, float> bestDir = { _agent.velocity.x, _agent.velocity.y };

	for (auto& dir : candidates)
	{
		int checkX = (int)(_agent.position.x + dir.first * 2);
		int checkY = (int)(_agent.position.y + dir.second * 2);

		float score = 0.0f;


		//Prefer directions with existing trails( follow the herd)
		if (mTrailStrength.count({ checkX,checkY }))
		{
			score += mTrailStrength[{checkX, checkY}] * mTrailAttraction;
		}

		score += rand01() * 0.5f;

		if (dir.first == _agent.velocity.x && dir.second == _agent.velocity.y)
		{
			score += 1.0f;
		}

		if (score > bestScore)
		{
			bestScore = score;
			bestDir = dir;
		}

	}

	return bestDir;
}

void CityGenerator::SolidifyAgentTrail(const RoadAgent& _agent)
{
	if (_agent.trail.size() < 2)
	{
		std::cout << "Trail too short to solidify" << std::endl;
		return;
	}

	std::cout << "Solidifying trail of " << _agent.trail.size() << " cells" << std::endl;

	// Convert each trail cell into a road
	for (int i = 0; i < _agent.trail.size(); ++i)
	{
		auto cell = _agent.trail[i];

		// Skip if already a road
		if (cityStatus[cell] == true)
			continue;

		// Mark as road
		cityStatus[cell] = true;

		// Figure out road direction based on neighbors in trail
		ROAD_DIRECTION dir = ROAD_DIRECTION::EAST; // default

		// Look at previous cell in trail
		if (i > 0)
		{
			auto prev = _agent.trail[i - 1];
			FixDirections(prev, cell);
		}

		// Look at next cell in trail
		if (i < _agent.trail.size() - 1)
		{
			auto next = _agent.trail[i + 1];
			FixDirections(cell, next);
		}

		// Also connect to any adjacent existing roads
		std::vector<std::pair<int, int>> neighbors = {
			{cell.first - 1, cell.second},
			{cell.first + 1, cell.second},
			{cell.first, cell.second - 1},
			{cell.first, cell.second + 1}
		};

		for (auto neighbor : neighbors)
		{
			if (cityStatus[neighbor] == true)
			{
				FixDirections(cell, neighbor);
			}
		}
	}
}

void CityGenerator::SpawnAgentFromRoad(int x, int y)
{
	// Get the road direction at this cell
	ROAD_DIRECTION rd = roadDirection[{x, y}];

	// Determine perpendicular directions to spawn agents
	std::vector<std::pair<float, float>> spawnDirections;

	// If road goes E-W, spawn N-S agents
	if (rd & (ROAD_DIRECTION::EAST | ROAD_DIRECTION::WEST))
	{
		spawnDirections.push_back({ 0.0f, 1.0f });  // North
		spawnDirections.push_back({ 0.0f, -1.0f }); // South
	}

	// If road goes N-S, spawn E-W agents
	if (rd & (ROAD_DIRECTION::NORTH | ROAD_DIRECTION::SOUTH))
	{
		spawnDirections.push_back({ 1.0f, 0.0f });  // East
		spawnDirections.push_back({ -1.0f, 0.0f }); // West
	}

	// Spawn 1-2 agents in perpendicular directions
	int numToSpawn = (rand01() < 0.5f) ? 1 : 2;

	for (int i = 0; i < numToSpawn && i < spawnDirections.size(); ++i)
	{
		// Pick a random perpendicular direction
		int idx = rand01() * spawnDirections.size();
		auto dir = spawnDirections[idx];

		// Add some random variation
		float angle = (rand01() - 0.5f) * 0.5f; // ±0.25 radians
		float cos_a = cos(angle);
		float sin_a = sin(angle);
		float newVx = dir.first * cos_a - dir.second * sin_a;
		float newVy = dir.first * sin_a + dir.second * cos_a;

		// Create new agent slightly offset from spawn point
		float spawnX = x + 0.5f + dir.first * 0.5f;
		float spawnY = y + 0.5f + dir.second * 0.5f;

		mAgents.push_back(RoadAgent(spawnX, spawnY, newVx, newVy));

		std::cout << "Spawned new agent at (" << spawnX << ", " << spawnY << ")" << std::endl;
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




