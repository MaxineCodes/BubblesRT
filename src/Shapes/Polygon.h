/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	Polygon.h
//
//	Description:
//	 Class for a 3-vertex polygon, 
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Shape.h"
#include "Vertex.h"


class Polygon
{
public:
    Vertex vertexA, vertexB, vertexC;

public:
    Polygon(Vertex vertexA, Vertex vertexB, Vertex vertexC);
    bool intersect(const RTRay& ray, float min, float max, rayHitRecord& record);
};