#pragma once
#include "../Datatypes/Vector3.h"

// Ray class
class RTRay
{
public:
	Vector3 m_origin;
	Vector3 m_direction;

public:
	// Default constructor
	RTRay() {}

	// Constructor
	RTRay(const Vector3& origin, const Vector3& direction)
	{
		m_origin = origin;
		m_direction = direction;
	}

	Vector3 getOrigin() const;
	Vector3 getDirection() const;
	Vector3 at(float t) const;
};

// Type aliases
using Ray = RTRay;