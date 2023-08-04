//
#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "../Shapes/Shape.h"
#include "../Cameras/Camera.h"
#include "../Cameras/PerspectiveCamera.h"


class Deserializer
{
public:
	// Parse scene file to usable data
	static std::vector<std::string>* parseSceneFile(const std::string& scenepath);

	// Serialize objects
	static PerspectiveCamera deserializeSceneCamera(std::vector<std::string>*& parsedSceneData);
	//static Shape deserializeSceneShape(std::vector<std::string>*& parsedSceneData, std::string& shapeName);
	//static Light deserializeLight(std::vector<std::string>* parsedSceneData);

	// Additional functions
	static int getShapeCount(std::vector<std::string>*& parsedSceneData);
	static std::vector<std::string> getShapeNames(std::vector<std::string>*& parsedSceneData);

	// Getter functions
	static const int getIntValue(
		std::vector<std::string>*& parsedFileData, const char* typeName, const char* key);

	static const float getFloatValue(
		std::vector<std::string>*& parsedFileData, const char* typeName, const char* key);

	static const std::string getStringValue(
		std::vector<std::string>*& parsedFileData, const char* typeName, const char* key);

	static const bool getBoolValue(
		std::vector<std::string>*& parsedFileData, const char* typeName, const char* key);

};

