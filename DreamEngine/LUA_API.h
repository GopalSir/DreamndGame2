#pragma once
#include <ECS_Core/Core.hpp>
#include <System/RenderSystem.hpp>
#include <Shape.hpp>
#include <Lua/include/lua.h>


namespace DREAM {
    class MyLuaAPI {
    private:
        static RenderSystem* renderSystem;

    public:
        static void Initialize(RenderSystem* rs);
        static void SpawnPoint(float x, float y, float z, float r, float g, float b, float a);

        // Lua binding functions
        static void RegisterLuaFunctions(lua_State* L);
    };
}
