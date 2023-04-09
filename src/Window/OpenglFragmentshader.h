#pragma once
#include <string>

std::string FragmentShader =
"#version 330 core\n"
"\n"
"layout(location=0) out vec4 color;\n"
"\n"
"void main()\n"
"{\n"
"	color=vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\n"
"";