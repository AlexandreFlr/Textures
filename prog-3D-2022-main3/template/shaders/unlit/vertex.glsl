#version 330 core

layout (location = 0) in vec3 pos;

out vec3 texCoord;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    texCoord = pos;
    vec4 position = projection * view * vec4(pos, 1.0);
    gl_Position = position.xyww;
}  

/*#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 ourColor;
out vec2 t_coord;

void main()
{
    gl_Position = vec4(position, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}*/

/*#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 color;
out vec2 TexCoord;

void main()
{
    gl_Position = projection * view * vec4(aPos, 1.0);
    color = aColor;
    TexCoord = aTexCoord;
}*/