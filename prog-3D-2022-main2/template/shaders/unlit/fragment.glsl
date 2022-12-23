#version 330 core
out vec4 FragColor;
  
in vec3 color;
in vec2 TexCoord;

uniform sampler2D colorTexture;

void main()
{
    FragColor = texture(colorTexture, TexCoord);
}