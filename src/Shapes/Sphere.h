/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	Sphere.h
//
//	Description:
//	 A sphere, the simplest 3D shape there is.
//	 Made up out of a position vector, a radius, and a pointer to a material.
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Shape.h"


class Sphere : public Shape
{
public:

    const char* m_name;
    Vector3 m_position;
    float m_radius;
    std::shared_ptr<Material> m_material;


public:

    Sphere(Vector3 position, float radius, std::shared_ptr<Material> material, const char* name = "default_name");

    virtual bool intersect(const RTRay& ray, float min, float max, rayHitRecord& record) const override;

};