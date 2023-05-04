// brrr
#pragma once

#include <string>
#include <vector>

#include "../DataTypes/Vector3.h"
#include "../RTCore/RTRay.h"


class PerspectiveCamera
{
public:
	std::string m_name = "temporary_name";

	Vector3 m_position;
	Vector3 m_lookDirection;
	Vector3 m_lowerLeftCorner;

	Vector3 m_viewUp;
	Vector3 m_horizontal, m_vertical;
	Vector3 m_u, m_v, m_viewVector;

	float m_lensSize;

public:

	// Camera Constructor
	PerspectiveCamera(
		Vector3 position,
		Vector3 lookDirection,
		Vector3 viewUp,
		
		float fov,
		float aspectRatio,
		float aperture,
		float focusDistance
	);

	// Default empty constructor
	PerspectiveCamera();

public:

	// Get the ray that is shot out into the scene
	RTRay getCamRay(float u, float v) const;

	std::string getType();

	std::string getName();

	PerspectiveCamera deserialize(std::vector<std::string>* sceneData);
};

