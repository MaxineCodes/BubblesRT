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
#include "../RTCore/RTObjectList.h"


class RTScene
{
private:

	std::string m_scenePath = "";
	std::string m_defaultScenepath = 
		"BubblesRT\\Scenes\\defaultScene.bubbles";

	std::vector<std::string> m_sceneFileData[3];

	// Camera
	PerspectiveCamera m_camera;

	// World object to contain all intersectable objects
	RTObjectList m_sceneObjectList;

	//std::vector<Material> m_materials;
	//std::vector<Light> m_lights;

public:
	const Colour skyGradientTop = Colour::White();
	const Colour skyGradientBottom = Colour::BubbleBlue();

public:

	// Default constructor
	RTScene(std::string& scenepath)
	{
		if (scenepath != "")
		{
			m_scenePath = scenepath;
			loadScene(scenepath);
		}

		else 
		{
			m_scenePath = m_defaultScenepath;
			loadScene(m_scenePath);
		}
	}

private:

	// Load the scene and start all the necessary functions.
	void loadScene(const std::string& scenepath);

	void loadMaterials(std::vector<std::string>*& parsedFileData);
	void loadShapes(std::vector<std::string>*& parsedFileData);

	void addShape(std::shared_ptr<Shape>);

	void createCameraFromFile(std::vector<std::string>* parsedFileData);
	void populateSceneFromFile();

	const std::string getFileStringValue(std::vector<std::string>* parsedFileData, const char* type, const char* key);

public:

	PerspectiveCamera getCamera();
	RTObjectList getObjectList();
	std::string getScenePath();
	std::string getSceneName();
	void printInfo();
};

