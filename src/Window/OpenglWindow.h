#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class OpenglWindow
{
private:
	std::string m_windowName = "WINDOW";
	int m_windowWidth = 640;
	int m_windowHeight = 480;

private:
	void SetWindowName(std::string windowName);
	void SetWindowSize(int width, int height);
	bool CreateWindow();

public:
	// Constructor
	OpenglWindow(std::string windowName, int windowWidth, int windowHeight);

public:
	// Draw an image to the screen
	void DrawImage();
	void ClearWindow();
};

