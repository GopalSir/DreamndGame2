// Lua integration and game headers
#include "../include/LuaIntegration.h"
#include "../include/MyGame.h"


MyGame* LuaIntegration::mygame;
lua_State* LuaIntegration::L;
//int LuaIntegration::lua_scroll_callback_ref = LUA_NOREF;
//LuaScrollEventHandler* LuaIntegration::scrollEventHandler = nullptr;

// Implement LuaScrollEventHandler
//int LuaScrollEventHandler::handleEvent(DREAM::EventInfo* _eventInfo)
//{
//	if (_eventInfo->getEventTypeCode() == DREAM::MouseScrollEvent::GetEventTypeCode())
//	{
//		DREAM::MouseScrollEvent* scrollEvent = dynamic_cast<DREAM::MouseScrollEvent*>(_eventInfo);
//		LuaIntegration::TriggerScrollCallback(scrollEvent->x_offset, scrollEvent->y_offset);
//	}
//	return 0;
//}


void LuaIntegration::run()
{
	mygame = new MyGame();

	// Register scroll event handler for Lua callbacks
	//scrollEventHandler = new LuaScrollEventHandler();
	//DREAM::EventSystem::registerEvent(DREAM::MouseScrollEvent::GetEventTypeCode(), scrollEventHandler);
	std::cout << "Lua scroll event handler registered!\n";
	

    L = luaL_newstate();
luaL_openlibs(L);

lua_newtable(L);
lua_pushcfunction(L, initEngineFromLua);
lua_setfield(L, -2, "init");

lua_pushcfunction(L, Lua_gizmoVisibility);
lua_setfield(L, -2, "gizmoVisibility");

lua_pushcfunction(L, Lua_SetBackGroundColor);
lua_setfield(L, -2, "SetBackGroundColor");

lua_pushcfunction(L, Lua_ClearScene);
lua_setfield(L, -2, "ClearScene");

//lua_pushcfunction(L, Lua_RegisterScrollCallback);
//lua_setfield(L, -2, "OnScroll");

// ENGINE.Shape table
lua_newtable(L);
lua_pushcfunction(L, Lua_Shape_GetRectangle);
lua_setfield(L, -2, "GetRectangle");

lua_pushcfunction(L, Lua_Shape_GetTriangle);
lua_setfield(L, -2, "GetTriangle");

lua_pushcfunction(L, Lua_Shape_GetPoint);
lua_setfield(L, -2, "GetPoint");

lua_setfield(L, -2, "Shape");   // ENGINE.Shape = Shape table




lua_setglobal(L, "ENGINE");     // global ENGINE

// Load game script
std::cout << "=== Loading Game Script ===\n";
if (luaL_dofile(L, "gameFile.lua") != LUA_OK) {
	const char* err = lua_tostring(L, -1);
	std::cout << "ERROR loading gameFile.lua: " << (err ? err : "unknown") << "\n";
	lua_pop(L, 1);
} else {
	std::cout << "gameFile.lua loaded successfully!\n";
}

	mygame->run();
}

int LuaIntegration::Lua_Shape_GetRectangle(lua_State* L)
{




	luaL_checktype(L, 1, LUA_TTABLE);

	VerticesComponent<float> vc;

	lua_getfield(L, 1, "vertices");
	luaL_checktype(L, -1, LUA_TTABLE);


	int vcount = (int)lua_rawlen(L, -1); // number of vertices

	//now we gotta pop 3 values for each vertex, but push it first. 
	for (int i = 1; i <= vcount; ++i)
	{
		lua_rawgeti(L, -1, i);
		luaL_checktype(L, -1, LUA_TTABLE);

		lua_rawgeti(L, -1, 1);
		float x = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);

		lua_rawgeti(L, -1, 2);
		float y = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);

		lua_rawgeti(L, -1, 3);
		float z = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);

		PositionComponent<float> vertex = PositionComponent<float>(x, y, z);
		vc.vertices.push_back(vertex);

		lua_pop(L, 1);
	}

	lua_pop(L, 1);

	//now we push colours
	lua_getfield(L, 1, "colors");
	luaL_checktype(L, -1, LUA_TTABLE);

	for (int i = 1; i <= vcount; ++i)
	{
		lua_rawgeti(L, -1, i);
		luaL_checktype(L, -1, LUA_TTABLE);

		lua_rawgeti(L, -1, 1);
		float r = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);

		lua_rawgeti(L, -1, 2);
		float g = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);

		lua_rawgeti(L, -1, 3);
		float b = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);


		lua_rawgeti(L, -1, 4);
		float a = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);

		COLOR clr = COLOR(r, g, b, a);
		vc.vertices_color.push_back(clr);

		lua_pop(L, 1);
	}

	lua_pop(L, 1);

	Entity* rectShape = Shape::GetRectangleShape(vc);
	int tempIndex = mygame->GetRenderSystem()->addEntity(rectShape);
	mygame->GetRenderSystem()->initEntityBuffers(tempIndex);

	return 0;
}

int LuaIntegration::Lua_Shape_GetTriangle(lua_State* L)
{




	luaL_checktype(L, 1, LUA_TTABLE);

	VerticesComponent<float> vc;

	lua_getfield(L, 1, "vertices");
	luaL_checktype(L, -1, LUA_TTABLE);


	int vcount = (int)lua_rawlen(L, -1); // number of vertices

	//now we gotta pop 3 values for each vertex, but push it first. 
	for (int i = 1; i <= vcount; ++i)
	{
		lua_rawgeti(L, -1, i);
		luaL_checktype(L, -1, LUA_TTABLE);

		lua_rawgeti(L, -1, 1);
		float x = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);

		lua_rawgeti(L, -1, 2);
		float y = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);

		lua_rawgeti(L, -1, 3);
		float z = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);

		PositionComponent<float> vertex = PositionComponent<float>(x, y, z);
		vc.vertices.push_back(vertex);

		lua_pop(L, 1);
	}

	lua_pop(L, 1);

	//now we push colours
	lua_getfield(L, 1, "colors");
	luaL_checktype(L, -1, LUA_TTABLE);

	for (int i = 1; i <= vcount; ++i)
	{
		lua_rawgeti(L, -1, i);
		luaL_checktype(L, -1, LUA_TTABLE);

		lua_rawgeti(L, -1, 1);
		float r = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);

		lua_rawgeti(L, -1, 2);
		float g = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);

		lua_rawgeti(L, -1, 3);
		float b = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);


		lua_rawgeti(L, -1, 4);
		float a = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);

		COLOR clr = COLOR(r, g, b, a);
		vc.vertices_color.push_back(clr);

		lua_pop(L, 1);
	}

	lua_pop(L, 1);

	Entity* rectShape = Shape::GetTriangleShape(vc);
	int tempIndex = mygame->GetRenderSystem()->addEntity(rectShape);
	mygame->GetRenderSystem()->initEntityBuffers(tempIndex);

	return 0;


	return 0;
}

int LuaIntegration::Lua_Shape_GetPoint(lua_State* L)
{
	// Same pattern as GetRectangle/GetTriangle - takes a vc table
	luaL_checktype(L, 1, LUA_TTABLE);

	VerticesComponent<float> vc;

	lua_getfield(L, 1, "vertices");
	luaL_checktype(L, -1, LUA_TTABLE);

	int vcount = (int)lua_rawlen(L, -1);

	for (int i = 1; i <= vcount; ++i)
	{
		lua_rawgeti(L, -1, i);
		luaL_checktype(L, -1, LUA_TTABLE);

		lua_rawgeti(L, -1, 1);
		float x = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);

		lua_rawgeti(L, -1, 2);
		float y = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);

		lua_rawgeti(L, -1, 3);
		float z = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);

		vc.vertices.push_back(PositionComponent<float>(x, y, z));

		lua_pop(L, 1);
	}

	lua_pop(L, 1);

	// Read colors
	lua_getfield(L, 1, "colors");
	luaL_checktype(L, -1, LUA_TTABLE);

	for (int i = 1; i <= vcount; ++i)
	{
		lua_rawgeti(L, -1, i);
		luaL_checktype(L, -1, LUA_TTABLE);

		lua_rawgeti(L, -1, 1);
		float r = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);

		lua_rawgeti(L, -1, 2);
		float g = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);

		lua_rawgeti(L, -1, 3);
		float b = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);

		lua_rawgeti(L, -1, 4);
		float a = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);

		COLOR clr = COLOR(r, g, b, a);
		vc.vertices_color.push_back(clr);

		lua_pop(L, 1);
	}

	lua_pop(L, 1);

	Entity* pointCloud = Shape::GetPointShape(vc);
	int tempIndex = mygame->GetRenderSystem()->addEntity(pointCloud);
	mygame->GetRenderSystem()->initEntityBuffers(tempIndex);

	return 0;
}

int LuaIntegration::Lua_gizmoVisibility(lua_State* L)
{
	float flag = (int)luaL_checknumber(L, -1);

	mygame->setupGizmo();

	return 0;
}

int LuaIntegration::Lua_SetBackGroundColor(lua_State* L)
{
	float r, g, b, a;

	r = luaL_checknumber(L, 1);
	g = luaL_checknumber(L, 2);
	b = luaL_checknumber(L, 3);
	a = luaL_checknumber(L, 4);


	COLOR color(r, g, b, a);
	mygame->setBackGroundColor(color);
	return 0;
}

int LuaIntegration::initEngineFromLua(lua_State* L)
{
	return 0;
}

int LuaIntegration::Lua_ClearScene(lua_State* L)
{
	// Clear all entities from render system
	// Note: This is a simplified version - in production you'd want proper cleanup
	//auto* renderSystem = mygame->GetRenderSystem();
	
	// Delete all entities
	//for (int i = renderSystem->entities.size() - 1; i >= 0; --i) {
	//	renderSystem->deleteEntity(i);
	//}
	//
	//// Clear the vector
	//renderSystem->entities.clear();
	
	std::cout << "Scene cleared!\n";
	return 0;
}

//int LuaIntegration::Lua_RegisterScrollCallback(lua_State* L)
//{
//	// Expect a function as the first argument
//	luaL_checktype(L, 1, LUA_TFUNCTION);
//	
//	// Store the function reference
//	lua_pushvalue(L, 1);  // Push function to top of stack
//	
//	// If we already have a callback, release it
//	if (lua_scroll_callback_ref != LUA_NOREF) {
//		luaL_unref(L, LUA_REGISTRYINDEX, lua_scroll_callback_ref);
//	}
//	
//	// Store new callback in registry
//	lua_scroll_callback_ref = luaL_ref(L, LUA_REGISTRYINDEX);
//	
//	std::cout << "Scroll callback registered from Lua!\n";
//	
//	return 0;
//}

//void LuaIntegration::TriggerScrollCallback(double xoffset, double yoffset)
//{
//	if (lua_scroll_callback_ref == LUA_NOREF || L == nullptr) {
//		return;  // No callback registered
//	}
//	
//	// Retrieve the function from registry
//	lua_rawgeti(L, LUA_REGISTRYINDEX, lua_scroll_callback_ref);
//	
//	// Push arguments
//	lua_pushnumber(L, xoffset);
//	lua_pushnumber(L, yoffset);
//	
//	// Call the function (2 arguments, 0 return values)
//	if (lua_pcall(L, 2, 0, 0) != LUA_OK) {
//		const char* err = lua_tostring(L, -1);
//		std::cout << "Error in scroll callback: " << (err ? err : "unknown") << "\n";
//		lua_pop(L, 1);
//	}
//}

