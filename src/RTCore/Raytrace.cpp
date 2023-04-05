#include "Raytrace.h"
#include <iostream>



Image Raytrace(const RTSettings& settings, const RTScene& scene, int sampleCount)
{

	std::cout << "RT.ImageWidth:  " << settings.ImageWidth << std::endl;
	std::cout << "RT.ImageHeight: " << settings.ImageHeight << std::endl;
	std::cout << "RT.RenderScale: " << settings.RenderScale << std::endl;
	

	return Image(50, 50, Colour::BubblePurple());
}
