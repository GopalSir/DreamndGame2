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
