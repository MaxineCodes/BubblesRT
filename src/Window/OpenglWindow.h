#pragma once

#include <iostream>

#include "../Datatypes/Image.h"
#include "../Datatypes/Colour.h"
#include "../RTCore/RTSettings.h"

class OpenglWindow
{
private:
	const char* m_windowName = "BubblesRT";
	int m_windowWidth = 20;
	int m_windowHeight = 20;

public:
	// Constructors
	OpenglWindow(const char* windowName, int windowWidth, int windowHeight);
	OpenglWindow(const char* windowName, const Image& image);
	OpenglWindow(const char* windowName, const RTSettings& raytraceSettings);

private:
	void SetWindowName(const char* windowName);
	void SetWindowSize(int width, int height);
	bool CreateWindow();

public:
	// Draw an Image to the screen
	void DrawImage(const Image& image);

	// Clear the window and fill with a Colour. 
	// If no Colour is given as a parameter, fill it with Magenta.
	void ClearWindow(const Colour& fillColour=Colour::Magenta());
};

