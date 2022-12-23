/*#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec3 pos;

uniform vec3 camPos;
uniform samplerCube cube;

void main()
{    
    vec3 dir = normalize(pos - camPos);
    vec3 refl = reflect(dir, normalize(normal));
    FragColor = vec4(texture(cube, refl).rgb, 1.0);
}*/

#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform sampler2D skybox;

void main()
{    
    FragColor = texture(skybox, TexCoords);
}