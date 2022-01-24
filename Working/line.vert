#version 330 core
layout (location = 0) in vec2 aPos; // the position variable has attribute position 0
  
out vec4 vertexColor; // specify a color output to the fragment shader

uniform vec4 colour;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(aPos, 0.0, 1.0);
    vertexColor = colour;
}