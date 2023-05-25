// Fragment Shader
#version 330 core

out vec4 fragmentColour;

in vec4 colour;
in vec2 uv;

uniform sampler2D fragmentTexture;

void main()
{
	//fragmentColour = vec4(0.81, 0.31, 0.92, 1.0);
	fragmentColour = texture(fragmentTexture, uv);
};

//layout(binding = 0) uniform sampler2D in_color;
//
//layout(location = 0) out vec4 out_color;
//
//in vec2 uv;
//
//void main()
//{
//	out_color = textureLod(in_color, uv.xy, 0);
//}