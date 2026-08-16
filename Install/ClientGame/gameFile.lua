--compile shader once
local myShaders = require("Shaders")
local myShapes = require("myShapes")

myShaderIndex1 = ENGINE.Shader.Compile(myShaders.defaultVertexShader,myShaders.defaultFragmentShader)
myShaderIndex2 = ENGINE.Shader.Compile(myShaders.defaultLightSourceVertexShader,myShaders.defaultLightSourceFragmentShader)
print("compiled shader ID =", myShaderIndex1)
print("compiled shader ID =", myShaderIndex2)
lightSoucePosition = {x = 50, y = 20, z = 50, w = 1.0}
ENGINE.Shader.SetUniform(myShaderIndex1, "ambient_light", {x = 0 ,y = 0.0, z = 0.0, w = 1.0}) -- Set a vec4 uniform for ambient light
ENGINE.Shader.SetUniform(myShaderIndex1, "light_position", lightSoucePosition) -- Set a vec3 uniform for light position



GMath = require("gameMath")

X_Span = 100
Y_Span = 100

Cell_Size = 10

TerrainVertices = {}
TerrainColors = {}
TerrainNormals = {}

for i=0,X_Span,Cell_Size do
    for j=0,Y_Span,Cell_Size do
        --calculate vertices counter clockwise
        table.insert(TerrainVertices,{i,0,j})
        table.insert(TerrainVertices,{i,0,j+Cell_Size})
        table.insert(TerrainVertices,{i+Cell_Size,0,j})

        table.insert(TerrainVertices,{i+Cell_Size,0,j})
        table.insert(TerrainVertices,{i,0,j+Cell_Size})
        table.insert(TerrainVertices,{i+Cell_Size,0,j+Cell_Size})

        table.insert(TerrainColors,{1,1,1,1})
        table.insert(TerrainColors,{1,1,1,1})
        table.insert(TerrainColors,{1,1,1,1})
        table.insert(TerrainColors,{1,1,1,1})
        table.insert(TerrainColors,{1,1,1,1})
        table.insert(TerrainColors,{1,1,1,1})

        



    end
end

for vertex

TerrainNormals = GMath.CalculateMeshNormals(TerrainVertices)

TerrainMesh = {
    vertices = TerrainVertices,
    colors = TerrainColors,
    normals = TerrainNormals
}

TerrainIdx = ENGINE.Shape.GetTriangle(TerrainMesh)
ENGINE.Shader.SetShader(TerrainIdx,myShaderIndex1)




function callbackFunction()
    
end