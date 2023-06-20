#include "RTScene.h"

#include "../Import/Deserializer.h"

#include "../Serialisation/Deserialiser.h"

#include <vector>


// Load the scene and create all the objects in the scene from the file
// given with the scene path.
void RTScene::loadScene(const std::string& scenepath)
{
	// Parse the data from the scene file
	std::vector<std::string>* parsedFileData = Deserializer::parseSceneFile(scenepath);

	// Get the camera from the scene file
	//m_camera = Deserializer::deserializeSceneCamera(parsedFileData);
	//createCameraFromFile(parsedFileData);

	const Vector3 camPosition(0, 1, 8);
	const Vector3 camLookDirection(0, 0, -1);
	const Vector3 viewUp(0, 1, 0);
	const float fov = 60;
	const float aperture = 0.0;
	const float focusDistance = (camPosition - camLookDirection).length();
	const float aspectRatio = 640 / 640;

	m_camera = PerspectiveCamera(
		camPosition,
		camLookDirection,
		viewUp,
		fov,
		aspectRatio,
		aperture,
		focusDistance);

	// Add shapes from the scene file to the sceneObjectList
	loadMaterials(parsedFileData);
	loadShapes(parsedFileData);
	
	//std::string fileAsString = parseFileToString(scenepath);
	//std::cout << fileAsString << std::endl;

	NodeWithChildren sceneRootNode = parseSceneFile(scenepath);
	std::cout << "sceneRootNode:" << sceneRootNode.m_nodeName << std::endl;

	Node cameraNode = sceneRootNode.getNode("CAMERA");
	std::string type = cameraNode.getValue("type");

	std::cout << type << std::endl;
}

void RTScene::loadShapes(std::vector<std::string>*& parsedFileData)
{
	auto material = std::make_shared<Lambert>(Colour::BubbleBlue());
	auto sphere1 = std::make_shared <Sphere>(Vector3(0, 0, 0), 0.50, material);

	auto material2 = std::make_shared<Lambert>(Colour::BubblePurple());
	auto sphere2 = std::make_shared <Sphere>(Vector3(-1.75, 0.25, 0), 0.75, material2);

	auto material3 = std::make_shared<Lambert>(Colour::Black());
	auto sphere3 = std::make_shared <Sphere>(Vector3(1.75, -0.25, 0), 0.35, material3);

	m_sceneObjectList.add(sphere1);
	m_sceneObjectList.add(sphere2);
	m_sceneObjectList.add(sphere3);


	auto groundmaterial = std::make_shared<Lambert>(Colour::BubbleHotpink());
	auto sphereGround = std::make_shared <Sphere>(Vector3(0, -100.5, 0), 100, groundmaterial);
	
	m_sceneObjectList.add(sphereGround);
};

void RTScene::addShape(std::shared_ptr<Shape> shape)
{
	m_sceneObjectList.add(shape);
}

void RTScene::loadMaterials(std::vector<std::string>*& parsedFileData)
{

}


const std::string RTScene::getFileStringValue(std::vector<std::string>* parsedFileData, const char* type, const char* key)
{
	std::string dataType = type;
	std::string dataKey = key;

	for (int i = 0; i < m_sceneFileData[0].size(); i++)
	{
		if (m_sceneFileData[0][i] == dataType)
		{
			if (m_sceneFileData[1][i] == dataKey)
			{
				return m_sceneFileData[2][i];
			}
		}
	}
	return "none";
}


// Creates a camera from data inside of the scene file
void RTScene::createCameraFromFile(std::vector<std::string>* parsedFileData)
{
	// Turn string data from file to usable data
	const float positionX = std::stof(getFileStringValue(parsedFileData, "cam", "positionx"));
	const float positionY = std::stof(getFileStringValue(parsedFileData, "cam", "positiony"));
	const float positionZ = std::stof(getFileStringValue(parsedFileData, "cam", "positionz"));
	const Vector3 camPosition(positionX, positionY, positionZ);

	const float lookDirectionX = std::stof(getFileStringValue(parsedFileData, "cam", "positionx"));
	const float lookDirectionY = std::stof(getFileStringValue(parsedFileData, "cam", "positiony"));
	const float lookDirectionZ = std::stof(getFileStringValue(parsedFileData, "cam", "positionz"));
	const Vector3 camLookDirection(lookDirectionX, lookDirectionY, lookDirectionZ);

	const Vector3 viewUp(0, 0, 0);

	const float fov = std::stof(getFileStringValue(parsedFileData, "cam", "fov"));
	const float aperture = std::stof(getFileStringValue(parsedFileData, "cam", "aperture"));
	const float focusDistance = std::stof(getFileStringValue(parsedFileData, "cam", "focusDistance"));

	const float imgWidth = std::stof(getFileStringValue(parsedFileData, "img", "width"));
	const float imgHeight = std::stof(getFileStringValue(parsedFileData, "img", "height"));
	const float aspectRatio = imgHeight / imgWidth;

	// Create perspective camera
	if (getFileStringValue(parsedFileData, "cam", "type") == "perspectivecamera")
	{
		m_camera = PerspectiveCamera(
			camPosition,
			camLookDirection,
			viewUp,
			fov,
			aspectRatio,
			aperture,
			focusDistance);
	}
}


void RTScene::populateSceneFromFile()
{
	//// Create a place to store all the shape names.
	//std::vector<std::string> shapesNamesInFile;
	//
	//// Get all the shape names and store them in the vector.
	//for (int i = 0; i < m_sceneFileData[0].size(); i++)
	//{
	//	if (m_sceneFileData[0][i] == "shape" && m_sceneFileData[1][i] == "name")
	//	{
	//		shapesNamesInFile.push_back(m_sceneFileData[2][i]);
	//	}
	//}
	//
	//for (int i = 0; i < shapesNamesInFile.size(); i++)
	//{
	//	const char* shapeName = shapesNamesInFile[i].c_str();
	//
	//	// Get the shape type
	//	const std::string shapeType = getFileStringValue(shapeName, "type");
	//
	//	if (shapeType == "sphere")
	//	{
	//		const float positionX = std::stof(getFileStringValue(shapeName, "positionx"));
	//		const float positionY = std::stof(getFileStringValue(shapeName, "positiony"));
	//		const float positionZ = std::stof(getFileStringValue(shapeName, "positionz"));
	//		const Vector3 shapePosition(positionX, positionY, positionZ);
	//
	//		const float radius = std::stof(getFileStringValue(shapeName, "radius"));
	//
	//		const std::string materialName = getFileStringValue(shapeName, "material");
	//	}
	//}
}


PerspectiveCamera RTScene::getCamera()
{
	return m_camera;
}

RTObjectList RTScene::getObjectList()
{
	return m_sceneObjectList;
}

std::string RTScene::getScenePath()
{
	return m_scenePath;
}


std::string RTScene::getSceneName()
{
	//return getFileStringValue("scene", "name");
	return "tmp_scene_name";
}


void RTScene::printInfo()
{
	std::cout << "====[ RTScene ]====================" << std::endl;
	std::cout << "Scene Name:   " << getSceneName() << std::endl;
	std::cout << "Scene Path:   " << getScenePath() << std::endl;
	std::cout << std::endl;
	std::cout << "Cam Type:     " << m_camera.getType() << std::endl;
	std::cout << "Cam Position: " << m_camera.m_position << std::endl;
	std::cout << "Cam Look Dir: " << m_camera.m_lookDirection << std::endl;
	std::cout << "Cam UV:       " << m_camera.m_u << " | " << m_camera.m_v << std::endl;
	std::cout << "===================================" << std::endl << std::endl;
}
