// Fragment Shader
#version 330 core

out vec4 fragmentColour;

in vec4 colour;
in vec2 uv;

uniform sampler2D fragmentTexture;

void main()
{
	fragmentColour = texture(fragmentTexture, uv);
};