#include "Image.h"

// Empty Image Constructor
Image::Image(int width, int height)
{
	m_width = width;
	m_height = height;
	m_pixelClr.reserve(width * height);
}

// Image with Fillcolour Contrustor
Image::Image(int width, int height, const Colour& fillColour)
{
	m_width = width;
	m_height = height;
	m_pixelClr.reserve(width * height);
}

int Image::GetWidth() { return m_width;}
int Image::GetHeight() { return m_height;}

void Image::InsertPixel(int u, int v, const Colour& pixelCltr)
{
	// Go to correct m_pixelClr index according to UV
	// Add pixelCltr to m_pixelClr
}

void Image::InsertPixelVector(const std::vector<Colour>& pixelCtrlVector)
{
	// Just replace the class vector
	m_pixelClr = pixelCtrlVector;
}
