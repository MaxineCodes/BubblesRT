#pragma once
#include <string>

std::string VertexShader =
"#version 330 core\n"
"\n"
"layout(location=0) in vec4 position;\n"
"\n"
"void main()\n"
"{\n"
"	gl_position = position;\n"
"}\n"
"";