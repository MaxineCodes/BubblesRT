// Fragment Shader
#version 420 core

//layout(location=0) out vec4 color;
//
//void main()
//{
//	color=vec4(0.81, 0.31, 0.92, 1.0);
//};

layout(binding = 0) uniform sampler2D in_color;

layout(location = 0) out vec4 out_color;

in vec2 uv;

void main()
{
	out_color = textureLod(in_color, uv.xy, 0);
}