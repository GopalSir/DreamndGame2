#include "LUA_API.h"

void DREAM::MyLuaAPI::Initialize(RenderSystem* rs)
{
	renderSystem = rs;		
}

void DREAM::MyLuaAPI::SpawnPoint(float x, float y, float z, float r, float g, float b, float a)
{
	Entity* tp = Shape::GetPointShape(x, y, z, COLOR(r, g, b, 1));
	renderSystem->initEntityBuffers(renderSystem->addEntity(tp));
}

void SpawnPoint(float x, float y, float z, float r, float g, float b, float a)
{

}

//register a free functions here to call the static function. lmao
void DREAM::MyLuaAPI::RegisterLuaFunctions(lua_State* L)
{
}
