#include "Deserializer.h"

std::vector<std::string>* Deserializer::parseSceneFile(const std::string& scenepath)
{
	std::fstream sceneFile;

	std::vector<std::string> fileData[3];

	// Reading scenefile
	sceneFile.open(scenepath, std::ios::in);
	if (sceneFile.is_open())
	{
		// Data comes in three sections : the type, the key, and the value.
		// Example: "cam type perspectivecamera".
		// So we store them as three vectors for easy iteration to write to later
		std::vector<std::string> dataTypes;
		std::vector<std::string> dataKeys;
		std::vector<std::string> dataValues;

		// ...And then I store all those vectors in an array.
		fileData[0] = dataTypes;
		fileData[1] = dataKeys;
		fileData[2] = dataValues;

		// Write the data from the scene file into the data vectors
		std::string dataType, dataKey, dataValue;
		while (sceneFile >> dataType >> dataKey >> dataValue)
		{
			fileData[0].push_back(dataType);
			fileData[1].push_back(dataKey);
			fileData[2].push_back(dataValue);
		}

		sceneFile.close();
	}

	return fileData;
}

PerspectiveCamera Deserializer::deserializeSceneCamera(std::vector<std::string>*& parsedSceneData)
{
	return PerspectiveCamera();
}

//Shape Deserializer::deserializeSceneShape(std::vector<std::string>*& parsedSceneData, std::string& shapeName)
//{
//	return Shape();
//}

int Deserializer::getShapeCount(std::vector<std::string>*& parsedSceneData)
{
	return 0;
}

std::vector<std::string> Deserializer::getShapeNames(std::vector<std::string>*& parsedSceneData)
{
	std::vector<std::string> shapeNames;

	for (int i = 0; i < parsedSceneData[0].size(); i++)
	{	
		if (parsedSceneData[0][i] == "shape")
		{
			if (parsedSceneData[1][i] == "name")
			{
				shapeNames.push_back(parsedSceneData[2][i]);
			}
		}
	}

	return shapeNames;
}

const int Deserializer::getIntValue(std::vector<std::string>*& parsedSceneData, const char* typeName, const char* key)
{
	std::string dataType = typeName;
	std::string dataKey = key;

	for (int i = 0; i < parsedSceneData[0].size(); i++)
	{
		if (parsedSceneData[0][i] == dataType)
		{
			if (parsedSceneData[1][i] == dataKey)
			{
				return std::stoi(parsedSceneData[2][i]);
			}
		}
	}
	return 0;
}

const float Deserializer::getFloatValue(std::vector<std::string>*& parsedSceneData, const char* typeName, const char* key)
{
	std::string dataType = typeName;
	std::string dataKey = key;

	for (int i = 0; i < parsedSceneData[0].size(); i++)
	{
		if (parsedSceneData[0][i] == dataType)
		{
			if (parsedSceneData[1][i] == dataKey)
			{
				return std::stof(parsedSceneData[2][i]);
			}
		}
	}
	return 0.0f;
}

const std::string Deserializer::getStringValue(std::vector<std::string>*& parsedSceneData, const char* typeName, const char* key)
{
	std::string dataType = typeName;
	std::string dataKey = key;

	for (int i = 0; i < parsedSceneData[0].size(); i++)
	{
		if (parsedSceneData[0][i] == dataType)
		{
			if (parsedSceneData[1][i] == dataKey)
			{
				return parsedSceneData[2][i];
			}
		}
	}
	return "0";
}

const bool Deserializer::getBoolValue(std::vector<std::string>*& parsedSceneData, const char* typeName, const char* key)
{
	std::string dataType = typeName;
	std::string dataKey = key;

	for (int i = 0; i < parsedSceneData[0].size(); i++)
	{
		if (parsedSceneData[0][i] == dataType)
		{
			if (parsedSceneData[1][i] == dataKey)
			{
				if (parsedSceneData[2][i] == "true")
					return true;

				if (parsedSceneData[2][i] == "1")
					return true;

				if (parsedSceneData[2][i] == "True")
					return true;

				else
					return false;
			}
		}
	}
	return false;
}
