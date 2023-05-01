#include "RTScene.h"

void RTScene::loadSceneFile(std::string scenepath)
{
	std::fstream sceneFile;

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
		m_fileData[0] = dataTypes;
		m_fileData[1] = dataKeys;
		m_fileData[2] = dataValues;
			

		// Write the data from the scene file into the data vectors
		std::string dataType, dataKey, dataValue;
		while (sceneFile >> dataType >> dataKey >> dataValue)
		{
			m_fileData[0].push_back(dataType);
			m_fileData[1].push_back(dataKey);
			m_fileData[2].push_back(dataValue);
		}

		createCameraFromFile();

		sceneFile.close();
	}
}

std::string RTScene::getFileStringValue(const char* type, const char* key)
{
	std::string dataType = type;
	std::string dataKey = key;

	for (int i = 0; i < m_fileData[0].size(); i++)
	{
		if (m_fileData[0][i] == dataType)
		{
			if (m_fileData[1][i] == dataKey)
			{
				return m_fileData[2][i];
			}
		}
	}
	return "No value found";
}

void RTScene::createCameraFromFile()
{
	float positionX = std::stof(getFileStringValue("cam", "positionx"));
	float positionY = std::stof(getFileStringValue("cam", "positiony"));
	float positionZ = std::stof(getFileStringValue("cam", "positionz"));
	Vector3 camPosition(positionX, positionY, positionZ);

	float lookDirectionX = std::stof(getFileStringValue("cam", "positionx"));
	float lookDirectionY = std::stof(getFileStringValue("cam", "positiony"));
	float lookDirectionZ = std::stof(getFileStringValue("cam", "positionz"));
	Vector3 camLookDirection(lookDirectionX, lookDirectionY, lookDirectionZ);

	float fov = std::stof(getFileStringValue("cam", "fov"));
	float aperture = std::stof(getFileStringValue("cam", "aperture"));
	float focusDistance = std::stof(getFileStringValue("cam", "focusDistance"));

	//float aspectRatio = std::stof(getFileStringValue(fileData, "cam", "fov"));

	std::cout << focusDistance << std::endl;
}

std::string RTScene::getScenePath()
{
	return m_scenePath;
}

std::string RTScene::getSceneName()
{
	return getFileStringValue("scene", "name");
}
