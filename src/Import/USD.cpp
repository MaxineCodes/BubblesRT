#include "USD.h"


const RTScene USD::constructDefaultScene(const char* filepath, RTSettings& settings)
{
    RTScene scene = RTScene(settings);

	const Vector3 camPosition(0, 1, 8);
	const Vector3 camLookDirection(0, 0, -1);
	const Vector3 viewUp(0, 1, 0);
	const float fov = 60;
	const float aperture = 0.0;

	scene.createCamera(
		camPosition,
		camLookDirection,
		viewUp,
		fov,
		aperture
	);

	auto material = std::make_shared<Lambert>(Colour::BubbleBlue());
	auto sphere1 = std::make_shared <Sphere>(Vector3(0, 0, 0), 0.50, material);
	
	auto material2 = std::make_shared<Lambert>(Colour::BubblePurple());
	auto sphere2 = std::make_shared <Sphere>(Vector3(-1.75, 0.25, 0), 0.75, material2);
	
	auto material3 = std::make_shared<Lambert>(Colour::Black());
	auto sphere3 = std::make_shared <Sphere>(Vector3(1.75, -0.15, 0), 0.35, material3);
	
	auto groundmaterial = std::make_shared<Lambert>(Colour::BubbleHotpink());
	auto sphereGround = std::make_shared <Sphere>(Vector3(0, -100.5, 0), 100, groundmaterial);
	
	scene.addShape(sphere1);
	scene.addShape(sphere2);
	scene.addShape(sphere3);
	scene.addShape(sphereGround);

    return scene;
}


const RTScene USD::constructSceneFromFile(const char* filepath, RTSettings& settings)
{
    RTScene scene = RTScene(settings);

    return scene;
}

const std::vector<Material> USD::getMaterialsFromFile(const char* filepath)
{
    return std::vector<Material>();
}

const std::vector<Mesh> USD::getMeshesFromFile(const char* filepath)
{
    return std::vector<Mesh>();
}

const Camera USD::getCameraFromFile(const char* filepath)
{
    return Camera();
}
