#pragma once

class Vector3
{
public:
	// Store floats as enum[3]
	float e[3];

	// Constructors
	const Vector3() : e{ 0,0,0 } {}
	const Vector3(float e0, float e1, float e2) : e{ e0, e1, e2 } {}

	// Get xyz floats
	float x() const { return e[0]; }
	float y() const { return e[1]; }
	float z() const { return e[2]; }


	//// Vector3 Method Definitions

	// Make negative
	Vector3 operator-() const;

	// Index access
	float operator[](int i) const;
	float& operator[](int i);

	// Add with another vector
	Vector3& operator+=(const Vector3 &vector);
	// Substract with another vector
	Vector3& operator-=(const Vector3 &vector);

	// Multiply vector by value
	Vector3& operator*=(const double value);
	// Divide vector by value
	Vector3& operator/=(const double value);

	// Handy maths
	double length() const;
	double length_squared() const;
	inline static Vector3 random();
	inline static Vector3 random(float min, float max);
	bool near_zero() const;
};

// Additional includes you will likely need if you're using Vector3
#include "../Maths/VectorMaths.h"
