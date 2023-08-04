#include "Raytrace.h"

#include <iostream>

#include "../RTCore/RTObjectList.h"

#include "../Maths/Maths.h"


// Global variables are usually kinda yucky
// but doing this otherwise would end up being
// more complicated than it needs to be.
// Simple = Good
Colour skyGradientTop;
Colour skyGradientBottom;


Image raytrace(RTSettings& settings, RTScene& scene, const int sampleCount)
{
	const int   imageWidth   = settings.getWidth();
	const int   imageHeight  = settings.getHeight();
	const bool  antialiasing = settings.getAntialiasing();
	const float renderScale  = settings.getRenderScale();

	// Assign the global variables a value
	skyGradientTop = scene.skyGradientTop;
	skyGradientBottom = scene.skyGradientBottom;

	PerspectiveCamera camera = scene.getCamera();

	Image RTOutput = Image(imageWidth, imageHeight);


	// Loop over every pixel..
	// it's a loop in reverse, otherwise the image outputs upside down
	for (int y = imageHeight; y > 0; y--)
	{
		std::cerr << "\rScanlines remaining: " << y-1 << ' ' << std::flush;
		for (int x = 0; x < imageWidth; x++)
		{
			// Final pixel colour to write to
			Colour pixelColour;

			// For every sample..
			for (int sample = 0; sample < sampleCount; sample++)
			{
				// Get uv coords.
				const float u = std::floor(x + 0.5f) / imageWidth;
				const float v = std::floor(y + 0.5f) / imageHeight;

				// Get a ray to shoot into the scene from the camera
				RTRay ray = camera.getCamRay(u, v);
				
				// Calculate the colour that ray must return
				pixelColour += calculateRayColour(ray, scene, settings);
			}

			// Scale the pixel colour according to the sample count
			pixelColour = scaleColourPerSample(pixelColour, sampleCount);

			// Write that final pixel colour to the output image
			RTOutput.insertPixel(pixelColour);
		}
	}
	std::cout << std::endl << "Render Finished." << std::endl;
	
	// Return the raytraced output image
	return RTOutput;
}


Colour calculateRayColour(RTRay ray, RTScene& scene, RTSettings& settings)
{
	const int  imageWidth  = settings.getWidth();
	const int  imageHeight = settings.getHeight();
	const bool depthDebug  = settings.getDepthDebug();

	// "Normal" ray tracing
	if (settings.getNormalDebug())
	{
		return raytraceRayNormalColour(
			ray,
			scene.getObjectList()
		);
	}

	// The actually normal ray tracing
	else 
	{
		return raytraceRay(
			ray,
			scene.getObjectList(),
			settings.getRayBounceCount()
		);
	}
}


// Trace the ray :)
Colour raytraceRay(
	const RTRay ray, 
	const RTObjectList& objectList, 
	const int bounces)
{
	// Follow the ray, and raytrace a new ray when an object is hit.
	// Creates new rays until the bounce count is used up.

	rayHitRecord record;

	// If we exceeded the bounce count, return black
	if (bounces <= 0) return Colour::Black();

	// If we hit an object,,
	if (objectList.hit(ray, 0.0001, INFINITY, record))
	{
		RTRay scatteredRay;
		Colour attenuation;

		// Scatter the ray according to the material
		if (record.m_material->scatter(ray, record, attenuation, scatteredRay))
		{
			//std::cout << record.m_material->m_name << std::endl;
			// Create a new ray to bounce until all the bounces are used up
			return attenuation * raytraceRay(
				scatteredRay, 
				objectList, 
				bounces - 1 // Once the bounces exceeded 0, it will return black
			);
		}

		return Colour::Black();
	}

	// If an object isn't hit, return the sky
	return skyGradient(ray);
}


// Trace the ray as normally but return the object normal vector as rgb
Colour raytraceRayNormalColour(
	const RTRay ray,
	const RTObjectList& objectList
	)
{
	// Similar to raytraceRay() except
	// it returns the normal vector as colour
	// of the object it hit.

	rayHitRecord record;

	// If an object is hit, return normal as colour
	if (objectList.hit(ray, 0.0001, INFINITY, record))
	{
		RTRay scatteredRay;
		Colour attenuation;

		// Convert XYZ to RGB
		float r = (record.m_normal.x() + 1) * 0.5;
		float g = (record.m_normal.y() + 1) * 0.5;
		float b = (record.m_normal.z() + 1) * 0.5;
		return Colour(r, g, b);
	}

	// If an object isn't hit, return the sky
	return skyGradient(ray);
}


// Get the sky colour according to the rays vector
Colour skyGradient(const RTRay ray)
{
	Vector3 unitDirection = unitVector(ray.getDirection());
	float t = 0.5 * (unitDirection.y() + 1.0);
	return (1.0 - t) * skyGradientBottom + t * skyGradientTop;
}


// Scale the colour according to the sample count
Colour scaleColourPerSample(Colour colour, const int sampleCount)
{
	// Higher sample count produces a higher colour value when
	// outputted by the raytracing function.
	// So we must make sure to scale the colour by the sample count.

	const float scale = 1.0 / sampleCount;
	float r = sqrt(scale * colour.r());
	float g = sqrt(scale * colour.g());
	float b = sqrt(scale * colour.b());
	return Colour(r, g, b);
}