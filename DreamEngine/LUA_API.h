#pragma once
#include <ECS_Core/Core.hpp>
#include <System/RenderSystem.hpp>
#include <Shape.hpp>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

namespace DREAM {
    class LUA_API {
    private:
        static RenderSystem* renderSystem;

    public:
        static void Initialize(RenderSystem* rs);
        static void SpawnPoint(float x, float y, float z, float r, float g, float b, float a);

        // Lua binding functions
        static void RegisterLuaFunctions(lua_State* L);
    };
}
