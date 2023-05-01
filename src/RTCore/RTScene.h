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
#include <fstream>
#include <iostream>

#include "../Cameras/PerspectiveCamera.h"
#include "../RTCore/RTObjectList.h"


class RTScene
{
private:

	std::string m_scenePath = "";
	std::string m_defaultScenepath = 
		"D:\\Dev\\2023\\BubblesRT\\BubblesRT\\Scenes\\defaultScene.bubbles";

	std::vector<std::string> m_fileData[3];

	// Camera
	PerspectiveCamera m_camera;

	// World object to contain all intersectable objects
	//RTObjectList sceneObjectList;

public:

	// Default constructor
	RTScene(std::string scenepath)
	{
		std::cout << "RTScene Constructor" << std::endl;

		if (scenepath != "")
		{
			m_scenePath = scenepath;
			loadSceneFile(scenepath);
		}

		else 
		{
			m_scenePath = m_defaultScenepath;
			loadSceneFile(m_scenePath);
		}
	}

private:

	void loadSceneFile(std::string scenepath);

	std::string getFileStringValue(const char* type, const char* key);
	
	void createCameraFromFile();

public:

	std::string getScenePath();
	std::string getSceneName();
};

