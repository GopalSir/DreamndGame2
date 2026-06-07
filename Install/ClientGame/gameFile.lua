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
ENGINE.Shader.SetUniform(myShaderIndex1, "ambient_light", {x = 0 ,y = 0.0, z = 0.0, w = 1.0}) -- Set a vec4 uniform for ambient light
ENGINE.Shader.SetUniform(myShaderIndex1, "light_position", {x = 1, y = 0, z = 1.0}) -- Set a vec3 uniform for light position



--make no assumption about the dimensions of the vector. 
function normalizeVector(v)
    local size = #(v)
    local length = 0
    for i = 1, size do
        length = length + v[i] ^ 2
    end
    length = math.sqrt(length)
    if length > 0 then
        for i = 1, size do
            v[i] = v[i] / length
        end
    end
    return v
end

function crossProduct(v1, v2)
    return {
        x = v1.y * v2.z - v1.z * v2.y,
        y = v1.z * v2.x - v1.x * v2.z,
        z = v1.x * v2.y - v1.y * v2.x
    }
end
--we will calculate vertex normals for each vertex in a triangle. 
-- we will loop through vertices in a triangle and calculate the normal for each vertex by taking the cross product of two edges
--function recieves 3 vertices of a triangle and returns normal vector for just that 1 face
function calculateFaceNormals(v1, v2, v3)
    local edge1 = {
        x = v2[1] - v1[1],
        y = v2[2] - v1[2],
        z = v2[3] - v1[3]
    }
    local edge2 = {
        x = v3[1] - v1[1],
        y = v3[2] - v1[2],
        z = v3[3] - v1[3]
    }
    local cross = crossProduct(edge1, edge2)
    local len = math.sqrt(cross.x^2 + cross.y^2 + cross.z^2)
    if len > 0 then
        return { cross.x/len, cross.y/len, cross.z/len }  -- array style
    else
        return { 0, 0, 1 }
    end
end

--funcion to calculate vertex normals for a triangle mesh.
--we iterate over 3 vertices at once and retrieve the normal vector and pushback the normal vector in the global table of that entity
function calculateMeshNormals(vertices)
    local normals = {}
    for i=1, #vertices,3 do
        local v1 = vertices[i]
        local v2 = vertices[i+1]
        local v3 = vertices[i+2]

        local faceNormal = calculateFaceNormals(v1,v2,v3)
        
        table.insert(normals,faceNormal)
        table.insert(normals,faceNormal)
        table.insert(normals,faceNormal)

    end
    return normals
end

newCube = myShapes.cube
newCube.normals = calculateMeshNormals(newCube.vertices) -- Calculate normals for the cube

--for loop generating 100 rangom rectangles 
for i = 1, 100 do
    local randomX = math.random(-50, 50)
    local randomY = math.random(-50, 50)
    local randomZ = math.random(-50, 50)
    

    local rectIdx = ENGINE.Shape.GetTriangle(newCube) -- Get a new rectangle index for each iteration
    
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
