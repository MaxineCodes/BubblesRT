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

	extern const Camera getCameraFromFile(const char* filepath);

	extern const std::vector<Mesh> getMeshesFromFile(const char* filepath);
	extern const std::vector<std::shared_ptr<Material>> getMaterialsFromFile(const char* filepath);

	extern const std::string extractMeshContent(const char* filepath, const std::string& meshName);
	extern const Mesh createMeshFromMeshContent(const std::string& meshContent);

	extern const std::string extractShaderContent(const char* filepath, const std::string& materialName);
	extern const std::shared_ptr<Material> createLambertFromShaderContent(const std::string& shaderContent, const std::string& name);

	// Returns an array of all the type names in the .USD file
	extern const std::vector<std::string> extractMeshNames(const char* filepath);
	extern const std::vector<std::string> extractMaterialNames(const char* filepath);

	extern const Vector2 convertUSDfloat2ToVector2(const std::string& value);
	extern const Vector3 convertUSDfloat3ToVector3(const std::string& value);
	extern const Vector3 convertUSDnormal3fToVector3(const std::string& value);
	extern const Colour convertUSDcolorf3ToColour(const std::string& value);

	extern const std::string extractExpressionValue(const std::string& content, const std::string& key);

	extern const std::string parseFileToString(const char* filepath);
	extern const std::string getDefinedTypeName(const char* type, const std::string& line);

	extern const std::string trim(const std::string& string);
}