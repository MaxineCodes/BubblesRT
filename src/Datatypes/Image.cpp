#include "Image.h"
#include <cmath>

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

	// Fill every pixel with a colour
	for (int y = 0; y < m_width; y++)
	{
		for (int x = 0; x < m_height; x++)
		{
			m_pixelClr.push_back(fillColour);
		}
	}
}

int Image::getWidth() { return m_width;}
int Image::getHeight() { return m_height;}

void Image::insertPixel( const Colour& pixelColour)
{
	m_pixelClr.push_back(pixelColour);
}

void Image::insertPixelVector(const std::vector<Colour>& pixelColourVector)
{
	// Just replace the class vector
	m_pixelClr = pixelColourVector;
}

Colour Image::getPixelColour(int u, int v)
{
	const float r = m_pixelClr[v * m_width + u].r();
	const float g = m_pixelClr[v * m_width + u].g();
	const float b = m_pixelClr[v * m_width + u].b();
	return Colour(r,g,b);
}

// Generate an image with some colours
Image Image::generateTestImage(int width, int height)
{
	// Image to output
	Image img(width, height);

	// Write some colours to the image
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			// Generate random colours
			const float r = float(x) / (width - 1);
			const float g = float(y) / (width - 1) / 0.8f;
			const float b = float(y) / (height - 1) + 0.5f;
			// Push back the colours into the image
			img.insertPixel(Colour(r, g, b));

		}
	}
	// Return image
	return img;
}

float* Image::unpackImage(const Image& image)
{
	const int pixelClrSize = (sizeof(image.m_pixelClr) / sizeof(float)) * 3;
	float pixels[pixelClrSize];

	int offset = 0;
	for (int i = 0; i < image.m_pixelClr.size(); i++)
	{
		pixels[i + offset] = image.m_pixelClr[i].r();
		offset += 1;
		pixels[i + offset] = image.m_pixelClr[i].g();
		offset += 1;
		pixels[i + offset] = image.m_pixelClr[i].b();
		offset += 1;
	}
	return pixels;
}

float* Image::unpack()
{
	const int pixelClrSize = (sizeof(m_pixelClr) / sizeof(float)) * 3;
	float pixels[pixelClrSize];

	int offset = 0;
	for (int i = 0; i < m_pixelClr.size(); i++)
	{
		pixels[i + offset] = m_pixelClr[i].r();
		offset += 1;
		pixels[i + offset] = m_pixelClr[i].g();
		offset += 1;
		pixels[i + offset] = m_pixelClr[i].b();
		offset += 1;
	}
	return pixels;
}
