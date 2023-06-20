/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	RTScene.h
//
//	Description:
//	 Scene object which holds all the data for all shapes, lights, materials, textures, etc
//	 for the raytracing algorithm to render.
//	 As well as containing the functionality to read scene files
// 
//	 An essential input for the raytrace function.
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "../Cameras/PerspectiveCamera.h"
#include "../Lights/Light.h"
#include "../RTCore/RTObjectList.h"
#include "../RTCore/RTSettings.h"


class RTScene
{
private:

	std::string m_scenePath = "";
	//std::string m_defaultScenepath = 
	//	"BubblesRT\\Scenes\\defaultScene.bubbles";

	std::string m_defaultScenepath =
		"D:\\Dev\\2023\\BubblesRT\\BubblesRT\\Scenes\\defaultScene.bubbles";

	// Camera
	PerspectiveCamera m_camera;

	// World object to contain all intersectable objects
	RTObjectList m_sceneObjectList;

	//std::vector<Material> m_materials;
	//std::vector<Light> m_lights;

	unsigned int m_imageWidth, m_imageHeight;

public:
	Colour skyGradientTop = Colour::White();
	Colour skyGradientBottom = Colour::BubbleBlue();

public:
	
	
	// Default constructor
	RTScene(RTSettings& settings)
	{
		m_imageWidth = settings.getWidth();
		m_imageHeight = settings.getHeight();
	}

public:

	void addShape(std::shared_ptr<Shape>);

	void createCamera(
		Vector3 camPosition,
		Vector3 camLookDirection,
		Vector3 viewUp,
		float fov,
		float aperture);

	void setSkyGradient(Colour top, Colour bottom);


public:

	PerspectiveCamera getCamera();
	RTObjectList getObjectList();
	std::string getScenePath();
	std::string getSceneName();
	void printInfo();
};

