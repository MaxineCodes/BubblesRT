#include "Raytrace.h"
#include <iostream>



Image raytrace(RTSettings& settings, RTScene& scene, const int sampleCount)
{
	// Get data from settings
	const int imageWidth = settings.getWidth();
	const int imageHeight = settings.getHeight();

	const float renderScale = settings.getRenderScale();
	const bool antialiasing = settings.getAntialiasing();
	const bool normalDebug = settings.getNormalDebug();
	const bool depthDebug = settings.getDepthDebug();

	// Prints
	printRTSettings(settings, sampleCount);
	printRTSceneInfo(scene);

	// Construct a blank image to render to
	Image RTOutput = Image(imageWidth, imageHeight);

	// Loop over every pixel
	for (int y = 0; y < imageHeight; y++) 
	{
		for (int x = 0; x < imageWidth; x++)
		{
			// For every pixel..

			// ..get uv coords..
			const float u = std::floor(x + 0.5f) / imageWidth;
			const float v = std::floor(y + 0.5f) / imageHeight;

			// ..get a ray to shoot into the scene from the camera..
			//RTRay ray = scene.camera.getCamRay(u, v);

			// ..do the raytracing algorithm..
			Colour pixelColour;
			//pixelColour + Colour();


			// ..which then gets added to the output image.
			RTOutput.insertPixel(pixelColour);



			//==== Just some temporary test code =======
			// Generate random colours
			const float r = float(x) / (imageWidth - 1);
			const float g = float(y) / (imageWidth - 1) / 0.8f;
			const float b = float(y) / (imageHeight - 1) + 0.5f;
			// Push back the colours into the image
			RTOutput.insertPixel(Colour(r, g, b));
			//==========================================
		}
	}
	

	// Return the raytraced output image
	return RTOutput;
}








void printRTSettings(RTSettings& settings, const int sampleCount)
{
	std::cout << "====[ RTSettings ]=================" << std::endl;
	std::cout << "Sample Count: " << sampleCount << std::endl;
	std::cout << "ImageWidth:   " << settings.getWidth() << std::endl;
	std::cout << "ImageHeight:  " << settings.getHeight() << std::endl;
	std::cout << "RenderScale:  " << settings.getRenderScale() << std::endl;
	std::cout << std::endl;
	if (settings.getAntialiasing())
		 std::cout << "Antialiasing: " << "Enabled" << std::endl;
	else std::cout << "Antialiasing: " << "Disabled" << std::endl;
	if (settings.getNormalDebug())
		 std::cout << "NormalDebug:  " << "Enabled" << std::endl;
	else std::cout << "NormalDebug:  " << "Disabled" << std::endl;
	if (settings.getDepthDebug())
		 std::cout << "DepthDebug:   " << "Enabled" << std::endl;
	else std::cout << "DepthDebug:   " << "Disabled" << std::endl;
	std::cout << "===================================" << std::endl << std::endl;
}

void printRTSceneInfo(RTScene& scene)
{
	std::cout << "====[ RTScene ]====================" << std::endl;
	std::cout << "Scene Name:   " << scene.getSceneName() << std::endl;
	std::cout << "Scene Path:   " << scene.getScenePath() << std::endl;
	//std::cout << std::endl;
	std::cout << "===================================" << std::endl << std::endl;
}
