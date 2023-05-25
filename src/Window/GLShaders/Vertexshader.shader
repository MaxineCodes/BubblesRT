// Vertex Shader
#version 330 core

layout(location=0) in vec4 vertexPosition;
layout(location=1) in vec4 vertexColour;
layout(location=2) in vec2 vertexUV;

out vec4 colour;
out vec2 uv;

void main()
{
	gl_Position = vertexPosition;
	colour = vertexColour;
	uv = vertexUV;
};