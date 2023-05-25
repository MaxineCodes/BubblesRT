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
	std::vector<Colour> m_pixelClr;

public:
	// Constructors
	Image(int width, int height);
	Image(int width, int height, const Colour& fillColour);

public:
	int getWidth();
	int getHeight();

	// Add an individual pixel according to the UV coords
	void insertPixel(const Colour& pixelColour);
	void insertPixelVector(const std::vector<Colour>& pixelCtrlVector);
	Colour getPixelColour(int u, int v);
	float* unpack();

	static Image generateTestImage(int width, int height);
	static float* unpackImage(const Image& image);
};