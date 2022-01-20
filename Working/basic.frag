#version 330 core
out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  
in vec2 TexCoord;

uniform sampler2D baseTexture;

void main()
{
    FragColor = texture(baseTexture, TexCoord) * vertexColor;
} 