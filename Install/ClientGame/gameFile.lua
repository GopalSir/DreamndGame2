-- Minimal triangle (tests CreateEntity + GUID path in C++).
-- Lua still gets the render-system index; entity GUID lives on the Entity in C++.

local myShaders = require("Shaders")
local myShapes = require("myShapes")

ENGINE.SetBackGroundColor(0.2, 0.06, 0.08, 0.5)
ENGINE.gizmoVisibility(1)

-- local idx = ENGINE.Shape.GetTriangle(myShapes.cat)
-- local idx2 = ENGINE.Shape.GetRectangle({
--     --only 4 vertices needed
--     vertices = {
--         { -0.5, -0.5, 0 }, { 0.5, -0.5, 0 }, { 0.5, 0.5, 0 }, { -0.5, 0.5, 0 }
--     },
--     colors = {
--         { 1, 0, 0, 1 }, { 1, 0, 0, 1 }, { 1, 0, 0, 1 }, { 1, 0, 0, 1 }
--     }
-- })


--compile shader once
myShaderIndex1 = ENGINE.Shader.Compile(myShaders.defaultVertexShader,myShaders.defaultFragmentShader)
print("compiled shader ID =", myShaderIndex1)
-- ENGINE.Shader.SetShader(idx2, myShaderIndex1)
ENGINE.Shader.SetUniform(myShaderIndex1, "ambient_light", {x = 0.5 ,y = 1.0, z = 1.0, w = 1.0}) -- Set a vec4 uniform for ambient light


--for loop generating 100 rangom rectangles 
for i = 1, 100 do
    local randomX = math.random(-50, 50)
    local randomY = math.random(-50, 50)
    local randomZ = math.random(-50, 50)
    
    local rectIdx = ENGINE.Shape.GetRectangle({
        vertices = {
            { -0.5, -0.5, 0 }, { 0.5, -0.5, 0 }, { 0.5, 0.5, 0 }, { -0.5, 0.5, 0 }
        },
        colors = {
            { math.random(), math.random(), math.random(), 1 }, 
            { math.random(), math.random(), math.random(), 1 }, 
            { math.random(), math.random(), math.random(), 1 }, 
            { math.random(), math.random(), math.random(), 1 }
        }
    })
    
    ENGINE.Physics.Set(rectIdx, { position = { x = randomX, y = randomY, z = randomZ }, velocity = { x = 0, y = 0, z = 0 } })
    ENGINE.Shader.SetShader(rectIdx, myShaderIndex1)
end

-- local cubeIndex = ENGINE.Shape.GetTriangle(myShapes.cube)
-- local cubeIndex2 = ENGINE.Shape.GetTriangle(myShapes.cube)

-- local catIndex = ENGINE.Shape.GetTriangle(myShapes.cat)




-- ENGINE.Shader.SetShader(cubeIndex, myShaderIndex1)
-- ENGINE.Shader.SetShader(cubeIndex2, myShaderIndex1)
-- ENGINE.Shader.SetShader(catIndex, myShaderIndex1)

-- ENGINE.Physics.Set(cubeIndex2,{position = {x = 0, y = 0, z = -30}})
-- -- ENGINE.Physics.Set(cubeIndex,{position = {x = 0, y = 0, z = -50}})
-- ENGINE.Physics.Set(catIndex,{position = {x = 0, y = 0, z = -50}})



-- print("[gameFile] render index =", cubeIndex)
-- print("[gameFile] add std::cout in CreateEntity or a Lua ENGINE.GetEntityId(idx) to print GUID")

function callbackFunction()

end

-- We'll we can do ENGINE.Entity.Destroy()
--                 ENGINE.Entity.Disable()
