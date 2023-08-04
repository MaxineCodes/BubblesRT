
#include "PerspectiveCamera.h"
#include "../Maths/Maths.h"


PerspectiveCamera::PerspectiveCamera(Vector3 position, Vector3 lookDirection, Vector3 viewUp, float fov, float aspectRatio, float aperture, float focusDistance)
{
	float theta = degreesToRadians(fov);
	float h = tan(theta / 2);

	float viewportHeight = 2.0 * h;
	float viewportWidth = aspectRatio * viewportHeight;

	m_viewVector = unitVector(position - lookDirection);
	m_lookDirection = lookDirection;

	m_u = unitVector(cross(viewUp, m_viewVector));
	m_v = cross(m_viewVector, m_u);

	m_horizontal = focusDistance * viewportWidth * m_u;
	m_vertical = focusDistance * viewportHeight * m_v;

	m_lowerLeftCorner = m_position - m_horizontal / 2 - m_vertical / 2 - focusDistance * m_viewVector;

	m_lensSize = aperture / 2;

	m_position = position;
}

PerspectiveCamera::PerspectiveCamera()
{
	// TEMPORARY
	Vector3 position = Vector3();
	Vector3 lookDirection = Vector3();
	float fov = 0;
	float aspectRatio = 0;
	float aperture = 0;
	float focusDistance = 0;

	float theta = degreesToRadians(fov);
	float h = tan(theta / 2);
	float viewportHeight = 2.0 * h;
	float viewportWidth = aspectRatio * viewportHeight;
	m_viewVector = unitVector(position - lookDirection);
	m_u = unitVector(cross(m_viewUp, m_viewVector));
	m_v = cross(m_viewVector, m_u);
	m_horizontal = focusDistance * viewportWidth * m_u;
	m_vertical = focusDistance * viewportHeight * m_v;
	m_lowerLeftCorner = m_position - m_horizontal / 2 - m_vertical / 2 - focusDistance * m_viewVector;
	m_lensSize = aperture / 2;
	m_position = position;
}

// Get the raytracing camera ray with random direction
RTRay PerspectiveCamera::getCamRay(float u, float v) const
{
	// Random-ish direction to shoot ray into
	Vector3 randomDirection = m_lensSize * randomUnitVectorDisk();

	// Create the UV offset of the ray with the randomn direction
	Vector3 offset = m_u * randomDirection.x() + m_v * randomDirection.y();
	//std::cout << m_u << " " << m_v << std::endl;
	//std::cout << "offset: " << offset << std::endl;

	// Construct a new ray and return it 
	return RTRay(m_position + offset, m_lowerLeftCorner + u * m_horizontal + v * m_vertical - m_position - offset);
}

std::string PerspectiveCamera::getType()
{
	return "perspectivecam" ;
}

std::string PerspectiveCamera::getName()
{
	return m_name;
}

PerspectiveCamera PerspectiveCamera::deserialize(std::vector<std::string>* sceneData)
{
	return PerspectiveCamera();
}
