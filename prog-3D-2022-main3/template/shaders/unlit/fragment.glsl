#version 330 core
out vec4 FragColor;

in vec3 texCoord;

uniform samplerCube cube;

void main()
{    
    FragColor = texture(cube, texCoord);
}