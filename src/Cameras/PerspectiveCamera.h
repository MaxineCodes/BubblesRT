// brrr
#pragma once

#include "../DataTypes/Vector3.h"
#include "../RTCore/RTRay.h"


class PerspectiveCamera
{
public:
	Vector3 position;
	Vector3 lookDirection;

	Vector3 viewUp;
	Vector3 horizontal, vertical;
	Vector3 u, v, viewVector;

public:
	// Camera Constructor
	PerspectiveCamera(
		Vector3 position,
		Vector3 lookDirection,
		
		float fov,
		float aspectRatio,
		float aperture,
		float focusDistance
	);
	// Default constructor
	PerspectiveCamera() {};

public:
	// Get the ray that is shot out into the scene
	RTRay getCamRay(float u, float v) const;
};

