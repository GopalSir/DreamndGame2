// Lua integration and game headers
#include "../include/LuaIntegration.h"
#include "../include/MyGame.h"


MyGame* LuaIntegration::mygame;
lua_State* LuaIntegration::L;
LuaCallbackSystem*  LuaIntegration::lcs;

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
	
	lcs = new LuaCallbackSystem();
	mygame->addGameSystem(lcs);

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

lua_newtable(L);
lua_pushcfunction(L, Lua_Shader_SetShader);
lua_setfield(L, -2, "SetShader");

lua_pushcfunction(L, Lua_Shader_SetUniform);
lua_setfield(L, -2, "SetUniform");

lua_setfield(L, -2, "Shader");   // ENGINE.Shader = Shader table


lua_newtable(L);
lua_pushcfunction(L, Lua_Physics_Set);
lua_setfield(L, -2, "Set");

lua_pushcfunction(L, Lua_Physics_Get);
lua_setfield(L, -2, "Get");

lua_setfield(L, -2, "Physics");


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

	lua_pushinteger(L, tempIndex);

	return 1;
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

	lua_pushinteger(L, tempIndex);

	return 1;

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
	
	lua_pushinteger(L, tempIndex);

	return 1;
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


//Set the physics component on an entity using index of that entity. 
//Physics componenet in C++ side has 4 fields. 
// If any field is missing from Lua argument, we simply not set that field value in Physics Component. 
int LuaIntegration::Lua_Physics_Set(lua_State* L)
{
	int entityIndex = luaL_checkinteger(L, 1);
	//std::cout << "Entity Index" << entityIndex << std::endl;


	//Entity* tempEntity = mygame->GetPhysicsSystem()->getEntity(entityIndex);

	/*PhysicsComponent* pc = tempEntity->getComponent<PhysicsComponent>();*/

	luaL_checktype(L, 2, LUA_TTABLE);


	PhysicsComponent* tempPC = nullptr;

	//If entity is already registered with physics 
	Entity* tempEntity = mygame->GetRenderSystem()->getEntity(entityIndex);
	if (tempEntity)
	{
		tempPC = tempEntity->getComponent<PhysicsComponent>();

		//if the entitiy has no PhysicsComponent
		if (!tempPC)
		{
			std::cout << "Rebuilding PC" << std::endl;
			tempPC = new PhysicsComponent();
			tempEntity->addComponent(tempPC);
			mygame->GetPhysicsSystem()->addEntity(tempEntity);
		}

	}

	float x,y,z;

	lua_getfield(L, 2, "position");
	if(lua_type(L, -1) != LUA_TTABLE)
	{
		lua_pop(L, 1);
	}
	else
	{
		
		lua_getfield(L, -1, "x");
		 x = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);
	
		lua_getfield(L, -1, "y");
		 y = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);
	
		lua_getfield(L, -1, "z");
		 z = (float)luaL_checknumber(L, -1);
		lua_pop(L, 1);
	
		tempPC->position.x = x;
		tempPC->position.y = y;
		tempPC->position.z = z;

		lua_pop(L, 1);
	}


	lua_getfield(L, 2, "velocity");
	if(lua_type(L, -1) != LUA_TTABLE)
	{
		lua_pop(L, 1);
	}
else {
		lua_getfield(L, -1, "x");
	 x = (float)luaL_checknumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "y");
	 y = (float)luaL_checknumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "z");
	 z = (float)luaL_checknumber(L, -1);
	lua_pop(L, 1);

	tempPC->velocity.x = x;
	tempPC->velocity.y = y;
	tempPC->velocity.z = z;
	lua_pop(L, 1);
}
	

	lua_getfield(L, 2, "rotation");
	if(lua_type(L, -1) != LUA_TTABLE)
	{
		lua_pop(L, 1);
	}
else{
		lua_getfield(L, -1, "x");
	x = (float)luaL_checknumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "y");
	y = (float)luaL_checknumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "z");
	z = (float)luaL_checknumber(L, -1);
	lua_pop(L, 1);

	tempPC->rotation.x = x;
	tempPC->rotation.y = y;
	tempPC->rotation.z = z;

	lua_pop(L, 1);
}

	//lua_getfield(L, 2, "rotation_velocity");
	//if (lua_type(L, -1) != LUA_TTABLE)
	//{
	//	lua_pop(L, 1);
	//}
	//else {
	//	lua_getfield(L, -1, "x");
	//	x = (float)luaL_checknumber(L, -1);
	//	lua_pop(L, 1);

	//	lua_getfield(L, -1, "y");
	//	y = (float)luaL_checknumber(L, -1);
	//	lua_pop(L, 1);

	//	lua_getfield(L, -1, "z");
	//	z = (float)luaL_checknumber(L, -1);
	//	lua_pop(L, 1);

	//	tempPC->rotation_velocity.x = x;
	//	tempPC->rotation_velocity.y = y;
	//	tempPC->rotation_velocity.z = z;

	//	lua_pop(L, 1);
	//}





	return 0;
}

int LuaIntegration::Lua_Physics_Get(lua_State* L)
{

	int entityIndex = luaL_checkinteger(L, 1);

	PhysicsComponent* tempPC;
	Entity* tempEntity = mygame->GetRenderSystem()->getEntity(entityIndex);
	if (tempEntity)
	{
		tempPC = tempEntity->getComponent<PhysicsComponent>();
		if (tempPC)
		{
			lua_newtable(L);
			lua_newtable(L);
			lua_pushnumber(L, tempPC->position.x);
			lua_setfield(L, -2, "x");
			lua_pushnumber(L, tempPC->position.y);
			lua_setfield(L, -2, "y");
			lua_pushnumber(L, tempPC->position.z);
			lua_setfield(L, -2, "z");
	
			
			lua_setfield(L, -2, "position");

			lua_newtable(L);
			lua_pushnumber(L, tempPC->velocity.x);
			lua_setfield(L, -2, "x");
			lua_pushnumber(L, tempPC->velocity.y);
			lua_setfield(L, -2, "y");
			lua_pushnumber(L, tempPC->velocity.z);
			lua_setfield(L, -2, "z");


			lua_setfield(L, -2, "velocity");

			lua_newtable(L);
			lua_pushnumber(L, tempPC->rotation.x);
			lua_setfield(L, -2, "x");
			lua_pushnumber(L, tempPC->rotation.y);
			lua_setfield(L, -2, "y");
			lua_pushnumber(L, tempPC->rotation.z);
			lua_setfield(L, -2, "z");
			lua_setfield(L, -2, "rotation");

			lua_newtable(L);
			lua_pushnumber(L, tempPC->rotation_velocity.x);
			lua_setfield(L, -2, "x");
			lua_pushnumber(L, tempPC->rotation_velocity.y);
			lua_setfield(L, -2, "y");
			lua_pushnumber(L, tempPC->rotation_velocity.z);
			lua_setfield(L, -2, "z");
			lua_setfield(L, -2, "rotation_velocity");

			
			return 1;
		}
		else
		{
			std::cout << "can't find PC for index " << entityIndex<<std::endl;
		}
		return 0;
	}
	
	return 0;
	
}

int LuaIntegration::Lua_Shader_SetShader(lua_State* L)
{
	
	int tempIndex= luaL_checkinteger(L,1);
	std::string vertexShader = luaL_checkstring(L, 2);
	std::string fragmentShader = luaL_checkstring(L, 3);



	auto& entities = mygame->GetRenderSystem()->entities;

	if (tempIndex < 0 || tempIndex >= entities.size())
		std::cout << "Can't set shader as the index provided by lua is invalid";
	else
		entities[tempIndex]->getComponent<DrawableComponent>()->shader = Shader::CreateFromSource(vertexShader.c_str(), fragmentShader.c_str());
	


	return 0;
}

int LuaIntegration::Lua_Shader_SetUniform(lua_State* L)
{
	int tempIndex = luaL_checkinteger(L, 1);
	std::string uniformName = luaL_checkstring(L, 2);
	float value = luaL_checknumber(L, 3);

	auto& entities = mygame->GetRenderSystem()->entities;

	if (tempIndex < 0 || tempIndex >= entities.size())
		std::cout << "Can't set shader as the index provided by lua is invalid";
	else
		entities[tempIndex]->getComponent<DrawableComponent>()->shader->setUniform(uniformName, value);


	return 0;
}

int LuaIntegration::SyncToLua()
{
	// Get or reuse existing INPUT table (don't recreate each frame!)
	lua_getglobal(L, "INPUT");
	if (!lua_istable(L, -1)) {
		// First time: create the table
		lua_pop(L, 1);  // Pop the nil
		lua_newtable(L);
	}
	// Now INPUT table is on top of stack

	// Get window handle from RenderSystem
	GLFWwindow* window = mygame->GetRenderSystem()->getWindow();

	// Loop over KeyState map
	for (auto const& entry : DREAM::KeyStates::KeyState) {
		int keyCode = entry.first;
		auto state = entry.second;

		const char* keyName = glfwGetKeyName(keyCode, 0);

		if (keyName) {
			// Set key state in table
			lua_pushboolean(L, state.first);
			lua_setfield(L, -2, keyName);
		}
		else {
			// Fallback for special keys
			std::string fallbackName = "KEY_" + std::to_string((int)keyCode);
			lua_pushboolean(L, state.first);
			lua_setfield(L, -2, fallbackName.c_str());
		}
	}

	// Add mouse position
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	lua_pushnumber(L, mouseX);
	lua_setfield(L, -2, "MOUSE_X");

	lua_pushnumber(L, mouseY);
	lua_setfield(L, -2, "MOUSE_Y");

	// Add mouse buttons
	lua_pushboolean(L, glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
	lua_setfield(L, -2, "MOUSE_LEFT");

	lua_pushboolean(L, glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);
	lua_setfield(L, -2, "MOUSE_RIGHT");

	lua_pushboolean(L, glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS);
	lua_setfield(L, -2, "MOUSE_MIDDLE");

	// Set back as global (table is still on stack)
	lua_setglobal(L, "INPUT");

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

