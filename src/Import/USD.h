/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	USD.h
//
//	Description:
//	 Contains functions and tools to parse USD ASCII scenes.
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include <string>

#include "../Cameras/Camera.h"
#include "../Lights/Light.h"
#include "../Shapes/Mesh.h"
#include "../Materials/Material.h"

#include "../RTCore/RTScene.h"

namespace USD
{
	extern const RTScene constructDefaultScene(const char* filepath, RTSettings& settings);
	extern const RTScene constructSceneFromFile(const char* filepath, RTSettings& settings);
	extern const std::vector<Material> getMaterialsFromFile(const char* filepath);
	extern const std::vector<Mesh> getMeshesFromFile(const char* filepath);
	extern const Camera getCameraFromFile(const char* filepath);
}