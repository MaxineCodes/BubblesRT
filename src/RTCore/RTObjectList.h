/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	RTObjectList.h
//
//	Description:
//	 A class which stores the objects in the scene.
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>

#include "../RTCore/RTCollision.h"
#include "../RTCore/RTRay.h"

#include "../DataTypes/Vector3.h"
#include "../Shapes/Shape.h"


class RTObjectList
{
public:
	std::vector<std::shared_ptr<Shape>> m_objects;

public:
	RTObjectList();
	RTObjectList(std::shared_ptr<Shape> object);

	bool hit(const RTRay& ray, float min, float max, rayHitRecord& record) const;
	void add(std::shared_ptr<Shape> object);
	void empty();
};

