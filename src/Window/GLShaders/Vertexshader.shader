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

//out gl_PerVertex
//{
//    vec4 gl_Position;
//};
//
//out vec2 uv;
//
//void main()
//{
//    float x = -1.0 + float((gl_VertexID & 1) << 2);
//    float y = -1.0 + float((gl_VertexID & 2) << 1);
//    uv.x = (x + 1.0) * 0.5;
//    uv.y = (y + 1.0) * 0.5;
//    gl_Position = vec4(x, y, 0, 1);
//}