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


extern float dot(const Vector3& vA, const Vector3& vB);
extern Vector3 cross(const Vector3& vA, const Vector3& vB);

extern Vector3 unitVector(Vector3 vector);
extern Vector3 randomUnitVector();
extern Vector3 randomUnitVectorSphere();
extern Vector3 randomUnitVectorDisk();

extern Vector3 reflect(const Vector3& vector, const Vector3& normal);
extern Vector3 refract(const Vector3& uv, const Vector3& normal, float etaiOverEtat);