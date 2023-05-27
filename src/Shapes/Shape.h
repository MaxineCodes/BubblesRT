/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	Shape.h
//
//	Description:
//	 Basic general shape interface.
//	 Defines what a shape must do. In this case, figure out of a ray intersects it or not.
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
	virtual bool intersect(const Ray& ray, float min, float max, rayHitRecord& record) const = 0;
};


#include "Sphere.h"
#include "Polygon.h"
#include "Mesh.h"