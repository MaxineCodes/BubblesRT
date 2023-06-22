/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	USD.h
//
//	Description:
//	 Contains functions and tools to parse .USD ASCII files into a RTScene object.
//	 This will be the interface between the raytracer and the .USD file.
// 
//	 Simply export a .USD file from Maya (or any other DCC) and pass it to the constructSceneFromFile function.
//   > Make sure to export the file as ASCII and not binary <
// 
//	 Not all functionality of the .USD file is supported, only the data which is compatible with this raytracer
//	 is parsed. This means that only meshes, lambert-materials and perspective-cameras are supported currently.
// 
// 
//  List of supported USD objects:
//   - Meshes
//   - Lambert materials
//   - Perspective cameras
//  
//  Note:
//   - Only one camera is supported, the first camera found in the .USD file will be used
//   - This raytracer does not support multiple materials per mesh, only the first material found will be used
// 
// 
//  This code is a bit messy, parsing strings directly without much abstraction. 
//  This may be improved in the future.
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
//Public functions

	// A default scene with a bunch of spheres, debugging purposes!
	extern const RTScene constructDefaultScene(const char* filepath, RTSettings& settings);

	// Turn the .USD ASCII file into a RTScene object so it may be sent to the raytracer
	extern const RTScene constructSceneFromFile(const char* filepath, RTSettings& settings);


//Private functions

	// Constructs the raytracing objects from the .USD file
	extern const Camera getCameraFromFile(const char* filepath);
	extern const std::vector<Mesh> getMeshesFromFile(const char* filepath);
	extern const std::vector<std::shared_ptr<Material>> getMaterialsFromFile(const char* filepath);

	// Get mesh data from the .USD file
	extern const std::vector<std::string> extractMeshNames(const char* filepath);
	extern const std::string extractMeshContent(const char* filepath, const std::string& meshName);
	extern const Mesh createMeshFromMeshContent(const std::string& meshContent);

	// Get material and shader data from the .USD file
	extern const std::vector<std::string> extractMaterialNames(const char* filepath);
	extern const std::string extractShaderContent(const char* filepath, const std::string& materialName);
	extern const std::shared_ptr<Material> createLambertFromShaderContent(const std::string& shaderContent, const std::string& name);

	// Returns an array of all the type names in the .USD file
	extern const std::vector<std::string> extractMeshNames(const char* filepath);
	extern const std::vector<std::string> extractMaterialNames(const char* filepath);

	// String value conversion functions
	extern const Vector2 convertUSDfloat2ToVector2(const std::string& value);
	extern const Vector3 convertUSDfloat3ToVector3(const std::string& value);
	extern const Vector3 convertUSDnormal3fToVector3(const std::string& value);
	extern const Colour convertUSDcolorf3ToColour(const std::string& value);

	// String line parsing helping functions
	extern const std::string extractExpressionValue(const std::string& content, const std::string& key);
	extern const std::string getDefinedTypeName(const char* type, const std::string& line);
	extern const std::string parseFileToString(const char* filepath);
	extern const std::string trim(const std::string& string);
}