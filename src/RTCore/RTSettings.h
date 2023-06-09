/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	RTSettings.h
//
//	Description:
//	 Holds raytracing settings such as output image size, renderscale, debug options, etc.
// 
//	 Is an essential input for the raytrace function.
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <iostream>


class RTSettings
{
public:
	// Image
	int m_imageWidth;
	int m_imageHeight;
	float m_renderScale = 1.0f;

	// Render
	int m_sampleCount = 1;
	int m_rayBounceCount = 10;
	bool m_antialiasing = false; // not yet implemented

	// Debug Render
	bool m_normalDebug = false;
	bool m_depthDebug = false; // not yet implemented


public:
	// Constructor
	RTSettings(int width, int height) 
	{
		m_imageWidth = width;
		m_imageHeight = height;
	}

public:
	// Methods
	int getWidth();
	int getHeight();
	float getRenderScale();
	const int getRayBounceCount();
	bool getAntialiasing();
	bool getNormalDebug();
	bool getDepthDebug();

	void setImageWidth(int width);
	void setImageHeight(int height);
	void setImageSize(int width, int height);

	void setRenderScale(float scale);
	void setAntiAliasing(bool enabled);
	void setNormalDebug(bool enabled);
	void setDepthDebug(bool enabled);

	void printInfo(const int sampleCount);
};