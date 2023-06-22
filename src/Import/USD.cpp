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


// Turn the .USD ASCII file into a RTScene object so it may be sent to the raytracer
const RTScene USD::constructSceneFromFile(const char* filepath, RTSettings& settings)
{
    RTScene scene = RTScene(settings);

	// Load and store all the materials from the USD file
	std::vector<std::shared_ptr<Material>> materials = getMaterialsFromFile(filepath);

	// Load and store all the meshes from the USD file
	// Meshes require materials to be loaded first
	std::vector<Mesh> meshes = getMeshesFromFile(filepath);

    return scene;
}


const std::vector<Mesh> USD::getMeshesFromFile(const char* filepath)
{
	std::vector<Mesh> meshes;
	std::vector<std::string> meshNames = extractMeshNames(filepath);

	for (unsigned int i = 0; i < meshNames.size(); i++)
	{
		std::string meshContent = extractMeshContent(filepath, meshNames[i]);
		//shaderContents.push_back(shaderContent);

		//std::cout << meshContent << std::endl;

		//if (shaderContent.find("\"lambert\""))
		//{
		//	std::cout << "Lambert";
		//	auto lambertMaterial = createLambertFromShaderContent(shaderContent);
		//	materials.push_back(lambertMaterial);
		//
		//}
	}

	return meshes;
}

const std::vector<std::shared_ptr<Material>> USD::getMaterialsFromFile(const char* filepath)
{
	std::vector<std::shared_ptr<Material>> materials;
	std::vector<std::string> materialNames = extractMaterialNames(filepath);

	for (unsigned int i = 0; i < materialNames.size(); i++)
	{
		std::string shaderContent = extractShaderContent(filepath, materialNames[i]);

		if (shaderContent.find("lambert", shaderContent.size()))
		{
			auto lambertMaterial = createLambertFromShaderContent(shaderContent, materialNames[i]);
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
	}

    return std::vector<std::shared_ptr<Material>>();
}

const std::string USD::extractMeshContent(const char* filepath, const std::string& meshName)
{
	std::string USDFileString = parseFileToString(filepath);

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

const Mesh USD::createMeshFromMeshContent(const std::string& meshContent)
{


	return Mesh();
}

const std::string USD::extractShaderContent(const char* filepath, const std::string& materialName)
{
	std::string USDFileString = parseFileToString(filepath);

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

const std::shared_ptr<Material> USD::createLambertFromShaderContent(const std::string& shaderContent, const std::string& name)
{
	Colour albedo = Colour::BubblePurple();

	std::string diffuseColour = extractExpressionValue(shaderContent, "color3f inputs:diffuseColor");
	albedo = convertUSDcolorf3ToColour(diffuseColour);

	return std::make_shared<Lambert>(albedo, name.c_str());
}

const Camera USD::getCameraFromFile(const char* filepath)
{
    return Camera();
}

const std::string USD::getDefinedTypeName(const char* type, const std::string& line)
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

const std::string USD::trim(const std::string& string)
{
	const char* ws = " \t\n\r\f\v";
	std::string str = string;

	str = str.erase(str.find_last_not_of(ws) + 1);
	str.erase(0, str.find_first_not_of(ws));

	return str;
}

const std::string USD::parseFileToString(const char* filepath)
{
	std::ifstream file(filepath);
	if (!file) {
		std::cerr << "Failed to open the file." << std::endl;
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

	std::string USDFileString = parseFileToString(filepath);
	std::istringstream USDFile(USDFileString);
	std::string line;
	
	while (std::getline(USDFile, line))
	{
		std::string value = getDefinedTypeName("Mesh", line);
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

	std::string USDFileString = parseFileToString(filepath);
	std::istringstream USDFile(USDFileString);
	std::string line;

	while (std::getline(USDFile, line))
	{
		std::string value = getDefinedTypeName("Material", line);
		if (value != "")
		{
			materialNames.push_back(value);
		}
	}

	return materialNames;
}

std::string trimWhitespace(const std::string& input) 
{
	size_t start = input.find_first_not_of(" \t");
	size_t end = input.find_last_not_of(" \t");

	if (start == std::string::npos || end == std::string::npos) 
	{
		// Input contains only whitespace characters
		return "";
	}

	return input.substr(start, end - start + 1);
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

const std::string USD::extractExpressionValue(const std::string& content, const std::string& key)
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