#pragma once

// Include engine headers first (which may include Windows.h via GLFW)
#include <string>
#include <map>
#include "MyGame.h"


// NOW include Lua headers (lua.hpp has extern "C" so C macro must be undefined first)
#include <Lua/include/lua.hpp>


class LuaCallbackSystem;


//This class will wrap around the engine, create engine instance
class LuaIntegration
{
	// Allow event handlers to access private members
	


	static LuaCallbackSystem* lcs;
	static MyGame* mygame;

	

	static int Lua_Shape_GetRectangle(lua_State* L);
	static int Lua_Shape_GetTriangle(lua_State* L);
	static int Lua_Shape_GetPoint(lua_State* L);
	static int Lua_gizmoVisibility(lua_State* L);
	static int Lua_SetBackGroundColor(lua_State* L);
	static int Lua_ClearScene(lua_State* L);
	//static int Lua_RegisterScrollCallback(lua_State* L);

	static int Lua_Physics(lua_State* L);

	static int Lua_Shader_SetShader(lua_State* L);
	static int Lua_Shader_SetUniform(lua_State* L);
	

	static int initEngineFromLua(lua_State* L);

	
	//static int lua_scroll_callback_ref;
	//static LuaScrollEventHandler* scrollEventHandler;
	
public:
	static void run();
	static lua_State* L;
	static int SyncToLua();
	//static void TriggerScrollCallback(double xoffset, double yoffset);
};




class LuaCallbackSystem : public System
{
	void update() override {

		LuaIntegration::SyncToLua();

		lua_getglobal(LuaIntegration::L, "callbackFunction");

		if (!lua_isfunction(LuaIntegration::L, -1)) {
			std::cout << "Function " << "callbackFunction" << " not found!" << std::endl;
			lua_pop(LuaIntegration::L, 1);  // Clean stack
			return;
		}

		// Call function (2 arguments, 1 return value)
		if (lua_pcall(LuaIntegration::L, 0, 0, 0) != LUA_OK) {
			std::cout << "Error calling function: " << lua_tostring(LuaIntegration::L, -1) << std::endl;
			lua_pop(LuaIntegration::L, 1);  // Pop error message
			return;
		}

	};
};