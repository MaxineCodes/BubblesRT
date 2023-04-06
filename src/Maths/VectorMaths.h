/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	VectorMath.h
//
//	Description:
//	 Mathy math functions using Vector3.
//	 Useful for, y'know, RT algorithms and such.
//	 
//	Automatically gets included when Vector3 is included.
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "../Datatypes/Vector3.h"


inline double dot(const Vector3& vA, const Vector3& vB);
inline Vector3 cross(const Vector3& vA, const Vector3& vB);

inline Vector3 unitVector(Vector3 vector);
static Vector3 randomUnitVector();
static Vector3 randomUnitVectorSphere();
static Vector3 randomUnitVectorDisk();

static Vector3 reflect(const Vector3& vector, const Vector3& normal);
static Vector3 refract(const Vector3& uv, const Vector3& normal, double etaiOverEtat);