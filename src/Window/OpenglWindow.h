/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	OpenglWindow.h
//
//	Description:
//	 Creates a OpenGL window to render the output raytrace image to.
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
	// Constructors
	//OpenglWindow(const char* windowName, int windowWidth, int windowHeight);
	OpenglWindow(const char* windowName, const Image& image);
	//OpenglWindow(const char* windowName, const RTSettings& raytraceSettings);

private:
	// Window
	void setWindowName(const char* windowName);
	void setWindowSize(int width, int height);
	bool createWindow(const Image& image);

private:
	// GL code
	static void emptyVAO();
	static std::string parseShaderFile(const std::string& filePath);
	static unsigned int compileGlShader(unsigned int type, const std::string& source);
	static unsigned int createGlShader(const std::string& vertexShader, const std::string& fragmentShader);
	static unsigned int createTexture(const Image& image);
	static void createRectangle(unsigned int VAO, unsigned int VBO, unsigned int EBO);

public:
	// Draw an Image to the screen
	void drawImage(const Image& image);

	// Clear the window and fill with a Colour. 
	// If no Colour is given as a parameter, fill it with Magenta.
	void clearWindow(const Colour& fillColour=Colour::Magenta());
};


