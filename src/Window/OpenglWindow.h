/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	OpenglWindow.h
//
//	Description:
//	 Viewport window to see raytrace render result in!
//	 This is the class where I dump all opengl related code, it is a bit messy
//	 but it does what it needs to do. 
// 
//	 This is a seperate thing to the renderer as it is not an integral part 
//   to any raytracing function.
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once


#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Datatypes/Image.h"
#include "../Datatypes/Colour.h"
#include "../RTCore/RTSettings.h"


class OpenglWindow
{
private:
	const char* m_windowName = "BubblesRT";
	int m_windowWidth = 20;
	int m_windowHeight = 20;
	GLFWwindow* m_window;

public:
	OpenglWindow(const char* windowName, const Image& image);

private:
	// Window
	void setWindowName(const char* windowName);
	void setWindowSize(int width, int height);
	bool createWindow(const Image& image);

private:
	// Opengl code
	static std::string parseShaderFile(const std::string& filePath);
	static unsigned int compileGlShader(unsigned int type, const std::string& source);
	static unsigned int createGlShader(const std::string& vertexShader, const std::string& fragmentShader);
	static unsigned int createTexture(const Image& image);
	static void createRectangle(unsigned int VAO, unsigned int VBO, unsigned int EBO);

public:
	// Clear the window and fill with a Colour. 
	// If no Colour is given as a parameter, fill it with Magenta.
	void clearWindow(const Colour& fillColour=Colour::Magenta());
};


