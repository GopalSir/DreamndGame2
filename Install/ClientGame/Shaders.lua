shaders  = {defaultVertexShader = [[
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec3 aNormal;

out vec4 vertexColor;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;



void main()
{

 gl_Position = projection_matrix*view_matrix*model_matrix*vec4(aPos,1.0);
 vertexColor = aColor;
 normal = aNormal;
 fragPos = vec3(model_matrix * vec4(aPos, 1.0));
}
]]
,
defaultFragmentShader = [[
#version 330 core

uniform vec4 ambient_light;
uniform vec3 light_position;

out vec4 fragColor;
in vec4 vertexColor;
in vec3 normal;
in vec3 fragPos;

void main()
{
	
	
    //vec4 baseColor = vec4(0.4, 0.7, 0.2, 1.0);
    fragColor = vertexColor * ambient_light; // Simple lighting calculation using vertex color and ambient light

    vec3 lightDir = normalize(light_position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    fragColor += vertexColor * diff; // Add diffuse lighting based on the normal and light direction

    
	
}
]]}

return shaders
