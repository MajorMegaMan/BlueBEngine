#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColour; // the colour variable has attribute position 1
layout (location = 2) in vec2 aTextCoord; // the colour variable has attribute position 2
  
out vec4 vertexColor; // specify a color output to the fragment shader
out vec2 TexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    vertexColor = vec4(aColour, 1.0);
	TexCoord = aTextCoord;
}