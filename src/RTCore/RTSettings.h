#pragma once

class RTSettings
{
public:
	// Image
	int ImageWidth = 400;
	int ImageHeight = 200;
	float RenderScale = 1.0f;

	// Render
	bool AntiAliasing = false;

	// Debug Render
	bool NormalDebug = false;
	bool DepthDebug = false;


public:
	// Constructor
	RTSettings(int width, int height) 
	{
		ImageWidth = width;
		ImageHeight = height;
	}
};