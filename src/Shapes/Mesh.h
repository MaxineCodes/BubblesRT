/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	Mesh.h
// 
// 
//  Description:  Mesh class for a mesh object made out of polygons.
//			      Best created from a file or a data structure.
// 				  
//				  A Mesh Shape is a collection of polygons, which are a collection of vertices.
//                Each vertex has a position, normal, and texture coordinate variable.
// 
//          	  Each polygon has an intersection function. 
//                When a Mesh intersection function is called, it will call each polygon's intersection function.
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>

#include "Shape.h"
#include "Polygon.h"


class Mesh : public Shape
{
public:
    const char* m_name;
    std::shared_ptr<Material> m_material;
    std::vector<std::shared_ptr<Polygon>> m_polygons;

public:

    Mesh(const char* name = "default_name");

    virtual bool intersect(const RTRay& ray, float min, float max, rayHitRecord& record) const override;

};