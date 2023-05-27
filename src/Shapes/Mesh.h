/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	Mesh.h
//
//	Description:
//	 Shape class for a mesh object made out of polygons. 
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>

#include "Shape.h"


class Mesh : public Shape
{
public:
    std::shared_ptr<Material> m_material;
    std::vector<std::shared_ptr<Polygon>> m_polygons;

public:

    Mesh();

    virtual bool intersect(const RTRay& ray, float min, float max, rayHitRecord& record) const override;

};