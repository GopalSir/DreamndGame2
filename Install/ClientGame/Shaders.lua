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
uniform vec4 light_position;

out vec4 fragColor;
in vec4 vertexColor;
in vec3 normal;
in vec3 fragPos;

void main()
{
	
	
    //vec4 baseColor = vec4(0.4, 0.7, 0.2, 1.0);
    fragColor = vec4(0.0, 0.0, 0.0, 1.0); // Start with black color
    //fragColor = vertexColor * ambient_light; // Simple lighting calculation using vertex color and ambient light

    vec3 testLightPos = vec3(0, 20.0, 0.0); // Example light position
    vec3 lightDir = normalize(light_position.xyz - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    fragColor += vertexColor * diff; // Add diffuse lighting based on the normal and light direction

    
	
}
]],

defaultLightSourceVertexShader = [[
#version 330 core

layout(location = 0) in vec3 aPos;



uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

uniform vec4 light_position;

void main()
{
    //First we need to translate the light source cube to the light position. We can do this by modifying the model matrix to include a translation to the light position.
    mat4 translationMatrix = mat4(1.0); // Identity matrix
    translationMatrix[3][0] = light_position.x; // Set the x component of the translation
    translationMatrix[3][1] = light_position.y; // Set the y component of the translation
    translationMatrix[3][2] = light_position.z; // Set the z component of the translation

        gl_Position = projection_matrix * view_matrix * translationMatrix * vec4(aPos, 1.0);
}
]],

defaultLightSourceFragmentShader = [[
#version 330 core
out vec4 fragColor;

void main()
{
    fragColor = vec4(1.0, 1.0, 1.0, 1.0); // Light source is rendered as white
}

]]

}

return shaders
