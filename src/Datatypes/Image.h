/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	Image.h
//
//	Description:
//	 A datatype to store a whole lot of Colours.
//	 Essentially a way to store full images in memory so we can draw it all in 1 draw call.
//	 It requires the width and height to be determined before constructing the Image.
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include "Colour.h"


class Image
{
public:
	int m_width;
	int m_height;
private:
	std::vector<Colour> m_pixelClr;

public:
	// Constructors
	Image(int width, int height);
	Image(int width, int height, const Colour& fillColour);

public:
	int GetWidth();
	int GetHeight();
	// Add an individual pixel according to the UV coords
	void InsertPixel(int u, int v, const Colour& pixelCltr);
	void InsertPixelVector(const std::vector<Colour>& pixelCtrlVector);
};

