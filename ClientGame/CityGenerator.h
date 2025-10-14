#pragma once
#include <ECS_Core/Core.hpp>
#include <Shape.hpp>
#include <random>
#include <algorithm>
#include <map>
#include <Lua/include/lua.hpp>
#include <IEventHandler.hpp>

enum CITY_BLOCK
{
	BUILDING,
	ROAD, 
	GRASS,

};

enum ROAD_TYPE
{
	BASIC,
	T_INTERSECTION,
	CORNER_BEND
};


enum ROAD_DIRECTION
{
	NORTH=1,
	NORTH_EAST=2,
	EAST=4,
	SOUTH_EAST=8,
	SOUTH=16,
	SOUTH_WEST=32,
	WEST=64,
	NORTH_WEST=128
};

class CityGenerator 
{
private:
	// This will decide how many meters of each city block map to. to multiply distances by this ig. not sure
	lua_State* mlua_State;
	float city_to_world_resolution;
	std::vector<Entity*> city;

	int city_x;
	int city_y;
	std::map<std::pair<int, int>,int> cityStatus;
	std::map<std::pair<int, int>, bool>initialBlocks;

	std::map<std::pair<int, int>, ROAD_DIRECTION> roadDirection;
	std::map<std::pair<int, int>, ROAD_TYPE> roadType;


	void GenerateRoad(int i,int j, DREAM::VerticesComponent<float>* _verticesComponent,COLOR _color);
	std::pair<int,int> FindNearestRoad(std::pair<int, int> _roadCoord, std::vector< std::pair<int, int>>_blockList);
	std::pair<int, int> MoveTowardsCoord(std::pair<int, int> _currentRoad, std::pair<int, int> _targetRoad);
	std::pair<int, int> FindAjdacentUnoccupied(std::pair<int, int> _currentRoad);
	int CountRoadNeighbors(std::pair<int, int> _coord);
	int ManhattanDistance(std::pair<int, int> _c1, std::pair<int, int> _c2);
	float EuclideanDistance(std::pair<int, int> _c1, std::pair<int, int> _c2);
	void FillTriangleBetweenBlock(std::pair<int, int> _c1, std::pair<int, int> _c2);
	void FixDirections(std::pair<int, int> _c1, std::pair<int, int> _c2);
	void DrawBounds();
	void PaintInitialBlocks(DREAM::VerticesComponent<float>*);

	int mIterationCount;
	float mgenerationProbability;
	float road_strip_width_percentage;
	COLOR roadColor;
	COLOR initialRoadColor;
	COLOR striPColor;

public:
	Entity* GetCity();
	CityGenerator();

};

