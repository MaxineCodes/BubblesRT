/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	Vector2.h
//
//	Description:
//	 Modified Vector3 class, but for only 2 floats.
//	 Ued for rendering 2D for the OpenGL context
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once


class Vector2
{
public:
	// Store floats as enum[2]
	float e[2];

	// Constructors
	const Vector2() : e{ 0,0 } {}
	const Vector2(float e0, float e1) : e{ e0, e1 } {}

	// Get xy floats OR uv floats
	float x() const { return e[0]; }
	float y() const { return e[1]; }
	float u() const { return e[0]; }
	float v() const { return e[1]; }

	// Presets
	static Vector2 None() { return Vector2(0.0, 0.0); }
};

// Type aliases
using Vector2f = Vector2;
using Point2f = Vector2;
using Point2 = Vector2;
