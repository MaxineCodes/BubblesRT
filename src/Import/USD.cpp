#include "USD.h"

#include <fstream>
#include <sstream>


// A default scene with a bunch of spheres, debugging purposes!
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
	auto sphere1 = std::make_shared<Sphere>(Vector3(0, 0, 0), 0.50, material);
	
	auto material2 = std::make_shared<Lambert>(Colour::BubblePurple());
	auto sphere2 = std::make_shared<Sphere>(Vector3(-1.75, 0.25, 0), 0.75, material2);
	
	auto material3 = std::make_shared<Lambert>(Colour::Black());
	auto sphere3 = std::make_shared<Sphere>(Vector3(1.75, -0.15, 0), 0.35, material3);
	
	auto groundmaterial = std::make_shared<Lambert>(Colour::BubbleHotpink());
	auto sphereGround = std::make_shared<Sphere>(Vector3(0, -100.5, 0), 100, groundmaterial);
	
	scene.addShape(sphere1);
	scene.addShape(sphere2);
	scene.addShape(sphere3);
	scene.addShape(sphereGround);

    return scene;
}


// Turn the .USD ASCII file into a RTScene object so it may be sent to the raytracer
const RTScene USD::constructSceneFromFile(const char* filepath, RTSettings& settings)
{
    RTScene scene = RTScene(settings);

	const Vector3 camPosition(24, 3, 22);
	const Vector3 camLookDirection(-4, 0, -1);
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

	// Load and store all the materials from the USD file
	//std::vector<std::shared_ptr<Material>> lambertMaterials = getMaterialsFromFile(filepath);

	// Load and store all the materials from the USD file
	MaterialHolder materialHolder;
	materialHolder.getMaterialsFromFile(filepath);
	materialHolder.printMaterials();

	// Load and store all the meshes from the USD file
	// Meshes require materials to be loaded first
	//std::vector<Mesh> meshes = getMeshesFromFile(filepath, materials);

	// DEBUG
	std::vector<Sphere> debugSpheres = getDebugSpheresFromFile(filepath, materialHolder);

	// Load and store all the lights from the USD file
	std::vector<std::shared_ptr<Light>> lights = getLightsFromFile(filepath); // TODO: Implement

	// Load the camera from the USD file
	//Camera camera = getCameraFromFile(filepath); // TODO: Implement

	/*
	// Add all the meshes as shapes to the scene
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		auto meshShape = std::make_shared<Mesh>(meshes[i]);
		scene.addShape(meshShape);
	}
	*/

	// Add all the DEBUG SPHERES as shapes to the scene
	for (unsigned int i = 0; i < debugSpheres.size(); i++)
	{
		auto debugSphereShape = std::make_shared<Sphere>(debugSpheres[i]);
		std::cout <<  "Adding debug sphere to scene" << std::endl; // DEBUG"
		scene.addShape(debugSphereShape);
	}

    return scene;
}


const std::vector<Mesh> USD::getMeshesFromFile(const char* filepath, MaterialHolder& materialsInFile)
{
	std::vector<Mesh> meshes;
	std::vector<std::string> meshNames = extractMeshNames(filepath);

	for (unsigned int i = 0; i < meshNames.size(); i++)
	{
		std::string meshName = meshNames[i];
		std::string meshContent = extractMeshContent(filepath, meshName);

		Mesh mesh = createMeshFromMeshContent(meshContent, materialsInFile);

		
	}

	return meshes;
}

// Practically the same as "getMeshesFromFile" but returns a vector of spheres created from some of the mesh data instead.
// Used for debugging and testing purposes, or if you want to be silly.
const std::vector<Sphere> USD::getDebugSpheresFromFile(const char* filepath, MaterialHolder& materialsInFile)
{
	std::vector<Sphere> spheres;
	std::vector<std::string> meshNames = extractMeshNames(filepath);

	for (unsigned int i = 0; i < meshNames.size(); i++)
	{
		std::string meshName = meshNames[i];
		std::string meshContent = extractMeshContent(filepath, meshName);

		auto Sphere = createDebugSphereFromMeshContent(meshContent, materialsInFile);

		spheres.push_back(Sphere);


	}

	return spheres;
}

const std::vector<std::shared_ptr<Lambert>> USD::getMaterialsFromFile(const char* filepath)
{
	std::vector<std::shared_ptr<Lambert>> materials;
	std::vector<std::string> materialNames = extractMaterialNames(filepath);

	for (unsigned int i = 0; i < materialNames.size(); i++)
	{
		std::string materialName = materialNames[i];

		//std::cout << "Material name: " << materialName << std::endl; // DEBUG


		std::string shaderContent = extractShaderContent(filepath, materialName);

		if (shaderContent.find("lambert", shaderContent.size()))
		{
			//std::cout << "LAMBERT FOUND" << std::endl; // DEBUG
			auto lambertMaterial = createLambertFromShaderContent(shaderContent, materialName);
			std::cout << "  " << lambertMaterial.get()->m_name << std::endl; // DEBUG
			//auto material = std::make_shared<Lambert>(lambertMaterial);

			materials.push_back(lambertMaterial);
		}

		/*
		if (shaderContent.find("lambert", shaderContent.size()))
		{
			std::cout << materialNames[i] << " material type: Lambert" << std::endl;
			auto lambertMaterial = createLambertFromShaderContent(shaderContent, materialNames[i]);
			materials.push_back(lambertMaterial);
		}
		*/

		else
			std::cout << "ERROR: Material type not found for " << materialNames[i] << std::endl; // DEBUG
	}

	for (unsigned int i = 0; i < materials.size(); i++)
	{
		std::cout << "  " << materials[i].get()->m_name << std::endl; // DEBUG
	}


    return materials;
}


const std::shared_ptr<Lambert> USD::getMaterialFromFile(const char* filepath, const char* materialName)
{
	std::shared_ptr<Lambert> material;
	std::vector<std::string> materialNames = extractMaterialNames(filepath);

	for (unsigned int i = 0; i < materialNames.size(); i++)
	{
		std::string materialName = materialNames[i];
		std::string shaderContent = extractShaderContent(filepath, materialName);

		if (materialNames[i].c_str() == materialName)
		{
			if (shaderContent.find("lambert", shaderContent.size()))
			{
				std::cout << "LAMBERT FOUND" << std::endl; // DEBUG
				auto lambertMaterial = createLambertFromShaderContent(shaderContent, materialName);
				//auto material = std::make_shared<Lambert>(lambertMaterial);

				return lambertMaterial;
			}
		}
	}

	std::cout << "NO MATERIAL FOUND" << std::endl; // DEBUG
	return material;
}


const std::vector<std::shared_ptr<Light>> USD::getLightsFromFile(const char* filepath)
{
	return std::vector<std::shared_ptr<Light>>();
}

const Camera USD::getCameraFromFile(const char* filepath)
{
	return Camera();
}

const std::string USD::extractMeshContent(const char* filepath, const std::string& meshName)
{
	std::string USDFileString = String::parseFileToString(filepath);

	size_t startPos = USDFileString.find('{');
	if (startPos != std::string::npos)
	{
		// Count the opening and closing braces to extract the string contents
		int braceCount = 1;
		size_t endPos = startPos + 1;
		while (endPos < USDFileString.length() && braceCount > 0)
		{
			if (USDFileString[endPos] == '{')
			{
				braceCount++;
			}
			else if (USDFileString[endPos] == '}')
			{
				braceCount--;
			}
			endPos++;
		}

		// Extract the string contents between the opening brace and the closing brace
		std::string contents = USDFileString.substr(startPos + 1, endPos - startPos - 2);
		std::cout << "Found mesh contents of: " << meshName << std::endl;
		return contents;
	}
	return "";
}

const Mesh USD::createMeshFromMeshContent(const std::string& meshContent, MaterialHolder& materialsInFile)
{


	return Mesh();
}


const Sphere USD::createDebugSphereFromMeshContent(const std::string& meshContent, MaterialHolder& materialsInFile)
{
	std::string materialName = extractMeshAssignedMaterialName(meshContent);
	std::cout << "materialName: " << materialName << std::endl;

	const auto meshMaterial = getLambertMaterialFromName(materialName.c_str(), materialsInFile);
	Vector3 meshPivotPosition = extractMeshPivotPosition(meshContent);

	const auto material = std::make_shared<Lambert>(Colour::BubbleBlue(), materialName.c_str());
	const Sphere sphere = Sphere(meshPivotPosition, 5.50, meshMaterial);

	return sphere;
}

const std::string USD::extractShaderContent(const char* filepath, const std::string& materialName)
{
	std::string USDFileString = String::parseFileToString(filepath);

	std::string materialLine = "def Material \"" + materialName + "\"";
	std::string shaderPrefix = "def Shader ";
	std::string materialPrefix = "def Material \"";

	size_t materialPos = USDFileString.find(materialLine);
	if (materialPos == std::string::npos)
		return "";  // Material line not found

	size_t shaderPos = USDFileString.find(shaderPrefix, materialPos);
	if (shaderPos == std::string::npos)
		return "";  // Shader block not found

	size_t shaderEndPos = USDFileString.find(materialPrefix, shaderPos + shaderPrefix.length());
	if (shaderEndPos == std::string::npos) 
		shaderEndPos = USDFileString.length();  // Assume end of text as shader block end

	size_t shaderBlockStart = shaderPos + shaderPrefix.length();
	std::string shaderContent = USDFileString.substr(shaderBlockStart, shaderEndPos - shaderBlockStart);
	std::cout << "Found shader contents of: " << materialName << std::endl;
	return shaderContent;
}

const std::shared_ptr<Lambert> USD::createLambertFromShaderContent(const std::string& shaderContent, const std::string& name)
{
	Colour albedo = Colour::BubblePurple();

	std::string diffuseColour = String::extractExpressionValue(shaderContent, "color3f inputs:diffuseColor");
	albedo = convertUSDcolorf3ToColour(diffuseColour);
	auto lambertMaterial = std::make_shared<Lambert>(albedo, name.c_str());
	//Lambert lambertMaterial = Lambert(albedo, name.c_str());

	return lambertMaterial;
}

const std::vector<std::shared_ptr<Light>> USD::extractLightNames(const char* filepath)
{
	return std::vector<std::shared_ptr<Light>>();
}

const std::string USD::String::getDefinedTypeName(const char* type, const std::string& line)
{
	std::string stringType = type;
	std::string key = "def " + stringType + " \"";

	size_t keyPos = line.find(key);
	if (keyPos != std::string::npos)
	{
		size_t valuePos = keyPos + key.length();
		size_t valueEndPos = line.find("\"", valuePos);
		if (valueEndPos != std::string::npos)
		{
			std::string value = line.substr(valuePos, valueEndPos - valuePos);
			return value;
		}
	}

	return "";
}

const std::string USD::String::trim(const std::string& string)
{
	const char* ws = " \t\n\r\f\v";
	std::string str = string;

	str = str.erase(str.find_last_not_of(ws) + 1);
	str.erase(0, str.find_first_not_of(ws));

	return str;
}

const std::string USD::String::parseFileToString(const char* filepath)
{
	std::ifstream file(filepath);
	if (!file) {
		std::cerr << "ERROR: FAILED TO OPEN USD FILE" << std::endl;
		return "";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string fileContents = buffer.str();

	file.close();
	return fileContents;
}

const std::vector<std::string> USD::extractMeshNames(const char* filepath)
{
	std::vector<std::string> meshNames;

	std::string USDFileString = String::parseFileToString(filepath);
	std::istringstream USDFile(USDFileString);
	std::string line;
	
	while (std::getline(USDFile, line))
	{
		std::string value = String::getDefinedTypeName("Mesh", line);
		if (value != "")
		{
			meshNames.push_back(value);
		}
	}

	return meshNames;
}


const std::vector<std::string> USD::extractMaterialNames(const char* filepath)
{
	std::vector<std::string> materialNames;

	std::string USDFileString = String::parseFileToString(filepath);
	std::istringstream USDFile(USDFileString);
	std::string line;

	while (std::getline(USDFile, line))
	{
		std::string value = String::getDefinedTypeName("Material", line);
		if (value != "")
		{
			//std::cout << "VALUE:" << value << std::endl;
			materialNames.push_back(value);
		}
	}

	return materialNames;
}

const std::shared_ptr<Lambert> USD::getLambertMaterialFromName(const char* name, MaterialHolder& materialsInFile)
{
	for (unsigned int i = 0; i < materialsInFile.m_lambertMaterials.size(); i++)
	{
		//std::cout << materialsInFile[i]->getName() << std::endl;
		if (materialsInFile.m_lambertMaterials[i]->getName() == name)
		{
			return materialsInFile.m_lambertMaterials[i];
		}

		std::cout << std::endl;
		std::cout << "ERROR: NO MATERIAL MATCHING NAME: " << name << std::endl;
		std::cout << "materialsInFile[i]: " << materialsInFile.m_lambertMaterials[i]->getName() << std::endl;
		std::cout << std::endl;

		// Return an obnoxiously magenta material if no material is found
		return std::make_shared<Lambert>(Colour(100,0,100), name);
	}
}

const Vector3 USD::extractMeshPivotPosition(const std::string& content)
{
	std::string pivotPositionString = String::extractExpressionValue(content, "float3 xformOp:translate:pivot");
	Vector3 pivotPosition = convertUSDfloat3ToVector3(pivotPositionString);
	return pivotPosition;
}

const Vector2 USD::convertUSDfloat2ToVector2(const std::string& value)
{
	return Vector2();
}

const Vector3 USD::convertUSDfloat3ToVector3(const std::string& value)
{
	return Vector3();
}

const Vector3 USD::convertUSDnormal3fToVector3(const std::string& value)
{
	return Vector3();
}

const Colour USD::convertUSDcolorf3ToColour(const std::string& value)
{
	// Remove the parentheses from the input string
	std::string inputValue = value.substr(1, value.length() - 2);
	std::istringstream valueSS(inputValue);

	// Split the string into 3 values
	std::string item;
	float floatValues[3]{ 0.0f, 0.0f, 0.0f };
	unsigned int i = 0;
	while (std::getline(valueSS, item, ',')) 
	{
		// Convert each token to float and add to the vector
		float value = std::stof(item);
		floatValues[i] = value;
		i++;
	}

	// Return a new colour value
	return Colour(floatValues[0], floatValues[1], floatValues[2]);
}

const std::string USD::extractMeshAssignedMaterialName(const std::string& content)
{
	// Will return something like "</lambert2SG>", we only want "lambert2SG"
	std::string materialName = String::extractExpressionValue(content, "rel material:binding");

	// Remove "<", ">", "/" characters from the name
	materialName.erase(remove(materialName.begin(), materialName.end(), '<'), materialName.end());
	materialName.erase(remove(materialName.begin(), materialName.end(), '>'), materialName.end());
	materialName.erase(remove(materialName.begin(), materialName.end(), '/'), materialName.end());

	return materialName;
}

const std::string USD::String::extractExpressionValue(const std::string& content, const std::string& key)
{
	std::istringstream contentSS(content);
	std::string line;
	std::string expressionKey = key;

	while (std::getline(contentSS, line))
	{
		// Find the equals sign position
		size_t equalsPosition = line.find('=');
		if (equalsPosition != std::string::npos)
		{
			// expression is the string before the equals sign
			// expressionValue is the string after the equals sign
			std::string exression = line.substr(0, equalsPosition);
			std::string exressionValue = line.substr(equalsPosition + 1);

			// Remove leading and trailing whitespaces
			line = trim(line);
			expressionKey = trim(expressionKey);
			exression = trim(exression);
			exressionValue = trim(exressionValue);

			if (exression == expressionKey)
			{
				return exressionValue;
			}
		}
	}

	return "";
}

const void USD::MaterialHolder::printMaterials()
{
	std::cout << "BASE MATERIALS:" << std::endl;
	for (unsigned int i = 0; i < m_baseMaterials.size(); i++)
		std::cout<< m_baseMaterials[i].get()->getName() << std::endl;

	std::cout << "LAMBERT MATERIALS:" << std::endl;
	for (unsigned int i = 0; i < m_lambertMaterials.size(); i++)
		std::cout << m_lambertMaterials[i].get()->getName() << std::endl;

	std::cout << std::endl;
	
}

const void USD::MaterialHolder::getMaterialsFromFile(const char* filepath)
{
	std::vector<std::string> materialNames = extractMaterialNames(filepath);

	for (unsigned int i = 0; i < materialNames.size(); i++)
	{
		std::string materialName = materialNames[i];
		std::string shaderContent = extractShaderContent(filepath, materialName);

		// Get lambert material
		if (shaderContent.find("lambert", shaderContent.size()))
		{
			std::cout << "LAMBERT FOUND: " << materialName << std::endl; // DEBUG
			std::shared_ptr<Lambert> lambertMaterial = createLambertFromShaderContent(shaderContent, materialName);

			m_lambertMaterials.push_back(lambertMaterial);
		}

		/*
		if (shaderContent.find("lambert", shaderContent.size()))
		{
			std::cout << materialNames[i] << " material type: Lambert" << std::endl;
			auto lambertMaterial = createLambertFromShaderContent(shaderContent, materialNames[i]);
			materials.push_back(lambertMaterial);
		}
		*/

		else
			std::cout << "ERROR: Material type not found for: " << materialName << std::endl; // DEBUG
	}
}
