/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	Shape.h
// 
// 
//  Description:  Basic general shape interface.
//			      Defines what a shape must do. In this case, figure out of a ray intersects it or not.
//				  Every shape has a name variable, a material name variable and an intersect function.
// 				  
//				  The name variable is used to identify the shape, which is later used to decide what material to assign.
//				  The intersect function is used to figure out if a ray intersects the shape or not, 
//					and will use the material to tell the ray what to do.
// 
//			      Every Shape type has its own constructor.
// 			      Every Shape has a material associated with it.
// 				  
// 				  
//  Types:		  Sphere: 
//					Basic sphere shape which is mathematically created from a center point and a radius.
// 
//				  Mesh: 
//					A more comples shape, see Mesh.h for more details.
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "../Materials/Material.h"
#include "../RTCore/RTRay.h"
#include "../Datatypes/Vector2.h"


class Shape 
{
public:
	const char* m_name;
	const char* m_materialName;
	virtual bool intersect(const Ray& ray, float min, float max, rayHitRecord& record) const = 0;
};


//#include "Sphere.h"
//#include "Polygon.h"
//#include "Mesh.h"