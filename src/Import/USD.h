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
//  Notes:
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


// Private classes

	// Holds all the materials to easily pass to other functions
	class MaterialHolder
	{
	public:
		std::vector<std::shared_ptr<Material>> m_baseMaterials;
		std::vector<std::shared_ptr<Lambert>> m_lambertMaterials;
		
	public:
		const std::vector<std::shared_ptr<Material>> getBaseMaterials() { return m_baseMaterials; }
		const std::vector<std::shared_ptr<Lambert>> getLambertMaterials() { return m_lambertMaterials; }
		const void printMaterials();
		const void getMaterialsFromFile(const char* filepath);
	};

//Private functions

	// Constructs the raytracing objects from the .USD file
	extern const std::vector<Mesh> getMeshesFromFile(const char* filepath, MaterialHolder& materialsInFile);
	extern const std::vector<std::shared_ptr<Lambert>> getMaterialsFromFile(const char* filepath);
	const std::shared_ptr<Lambert> getMaterialFromFile(const char* filepath, const char* materialName);
	extern const std::vector<std::shared_ptr<Light>> getLightsFromFile(const char* filepath);
	extern const Camera getCameraFromFile(const char* filepath);

	// Create a sphere from the mesh data from the .USD file (debugging purposes)
	extern const std::vector<Sphere> getDebugSpheresFromFile(const char* filepath, MaterialHolder& materialsInFile);

	// Get mesh data from the .USD file
	extern const std::vector<std::string> extractMeshNames(const char* filepath);
	extern const std::string extractMeshContent(const char* filepath, const std::string& meshName);
	extern const Mesh createMeshFromMeshContent(const std::string& meshContent, MaterialHolder& materialsInFile);

	// Get sphere data from the mesh data from the .USD file (debugging purposes)
	extern const Sphere createDebugSphereFromMeshContent(const std::string& meshContent, MaterialHolder& materialsInFile);

	// Get material and shader data from the .USD file
	extern const std::vector<std::string> extractMaterialNames(const char* filepath);
	extern const std::string extractShaderContent(const char* filepath, const std::string& materialName);
	extern const std::shared_ptr<Lambert> createLambertFromShaderContent(const std::string& shaderContent, const std::string& name);

	// Get light data from the .USD file
	extern const std::vector<std::shared_ptr<Light>> extractLightNames(const char* filepath);

	// Returns an array of all the type names in the .USD file
	extern const std::vector<std::string> extractMeshNames(const char* filepath);
	extern const std::vector<std::string> extractMaterialNames(const char* filepath);

	extern const std::shared_ptr<Lambert> getLambertMaterialFromName(const char* name, MaterialHolder& materialsInFile);

	// Get values from the .USD file
	extern const std::string extractMeshAssignedMaterialName(const std::string& content);
	extern const Vector3* extractMeshExtent(const std::string& content);
	extern const int* extractMeshFaceVertexCounts(const std::string& content);
	extern const int* extractMeshFaceVertexIndices(const std::string& content);
	extern const Vector3* extractMeshPoints(const std::string& content);
	extern const Vector3 extractMeshPivotPosition(const std::string& content);

	// String value conversion functions
	extern const Vector2 convertUSDfloat2ToVector2(const std::string& value);
	extern const Vector3 convertUSDfloat3ToVector3(const std::string& value);
	extern const Vector3 convertUSDfloat3ArrToVector3Arr(const std::string& value);
	extern const Vector3 convertUSDintArrToIntArr(const std::string& value);
	extern const Vector3 convertUSDnormal3fToVector3(const std::string& value);
	extern const Colour convertUSDcolorf3ToColour(const std::string& value);

	namespace String
	{
		// String line parsing helping functions
		extern const std::string extractExpressionValue(const std::string& content, const std::string& key);
		extern const std::string getDefinedTypeName(const char* type, const std::string& line);
		extern const std::string parseFileToString(const char* filepath);
		extern const std::string trim(const std::string& string);
	}
}