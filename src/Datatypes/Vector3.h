/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	Vector3.h
//
//	Description:
//	 Vector3 class based on floats. Complete with Vector3 and float operators.
//	 Based on the Vector3 implementation found in RTWeekend
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
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

	// operator methods
	Vector3& operator+=(const Vector3 &vector);
	Vector3& operator-=(const Vector3 &vector);
	Vector3& operator*=(const double value);
	Vector3& operator/=(const double value);

	// Handy maths
	double length() const;
	double lengthSquared() const;
	inline static Vector3 random();
	inline static Vector3 random(float min, float max);
	bool nearZero() const;

	// Presets
	static Vector3 None() { return Vector3(0.0, 0.0, 0.0); }
};

// extern inline Vector3 operator methods
extern inline Vector3 operator+(const Vector3& u, const Vector3& v);
extern inline Vector3 operator-(const Vector3& u, const Vector3& v);
extern inline Vector3 operator*(const Vector3& u, const Vector3& v);
extern inline Vector3 operator*(double t, const Vector3& v);
extern inline Vector3 operator*(const Vector3& v, double t);
extern inline Vector3 operator/(Vector3 v, double t);

// Type aliases
using Vector3f = Vector3;
using Point3f = Vector3;
using Point3 = Vector3;

// Additional includes you will likely need if you're using Vector3
#include "../Maths/VectorMaths.h"
