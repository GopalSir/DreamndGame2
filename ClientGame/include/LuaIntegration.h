#pragma once

// Include engine headers first (which may include Windows.h via GLFW)
#include <string>
#include <map>
#include "MyGame.h"


// NOW include Lua headers (lua.hpp has extern "C" so C macro must be undefined first)
#include <Lua/include/lua.hpp>



//This class will wrap around the engine, create engine instance
class LuaIntegration
{
	// Allow event handlers to access private members
	

	static MyGame* mygame;

	static int Lua_Shape_GetRectangle(lua_State* L);
	static int Lua_Shape_GetTriangle(lua_State* L);
	static int Lua_Shape_GetPoint(lua_State* L);
	static int Lua_gizmoVisibility(lua_State* L);
	static int Lua_SetBackGroundColor(lua_State* L);
	static int Lua_ClearScene(lua_State* L);
	//static int Lua_RegisterScrollCallback(lua_State* L);

	static int initEngineFromLua(lua_State* L);

	static lua_State* L;
	//static int lua_scroll_callback_ref;
	//static LuaScrollEventHandler* scrollEventHandler;
	
public:
	static void run();
	//static void TriggerScrollCallback(double xoffset, double yoffset);
};



