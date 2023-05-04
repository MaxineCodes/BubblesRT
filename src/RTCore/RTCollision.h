// Blep
#pragma once

#include "../Datatypes/Vector3.h"
#include "../Materials/Material.h"
#include "../RTCore/RTRay.h"

class Material;


class RTCollision
{

};

struct rayHitRecord
{
    Vector3 m_p;
    Vector3 m_normal;
    std::shared_ptr<Material> m_material;
    float m_t{};

    bool frontFace{};

    // Calculate normal face
    inline void setFaceNormal(const RTRay& ray, const Vector3& outwardNormal)
    {
        frontFace = dot(ray.getDirection(), outwardNormal) < 0;
        m_normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

