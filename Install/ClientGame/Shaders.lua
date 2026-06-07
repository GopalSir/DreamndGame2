shaders  = {defaultVertexShader = [[
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;

out vec4 vertexColor;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;



void main()
{

 gl_Position = projection_matrix*view_matrix*model_matrix*vec4(aPos,1.0);
 vertexColor = aColor;
}
]]
,
defaultFragmentShader = [[
#version 330 core

uniform vec4 ambient_light;

out vec4 fragColor;
in vec4 vertexColor;



void main()
{
	
	
    //vec4 baseColor = vec4(0.4, 0.7, 0.2, 1.0);
    fragColor = vertexColor * ambient_light; // Simple lighting calculation using vertex color and ambient light
	
}
]]}

return shaders
