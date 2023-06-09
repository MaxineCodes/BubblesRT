/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	Mesh.h
//
//	Description:
//	 Shape class for a mesh object made out of polygons. 
//   Best created from a file or a data structure.
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