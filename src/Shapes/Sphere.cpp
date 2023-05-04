#include "Sphere.h"

Sphere::Sphere(Vector3 position, float radius, std::shared_ptr<Material> material)
{
    m_position = position;
    m_radius = radius;
    m_material = material;
}

bool Sphere::intersect(const RTRay& ray, float min, float max, rayHitRecord& record) const
{
    Vector3 oc = ray.getOrigin() - m_position;
    auto a = ray.getDirection().lengthSquared();
    auto half_b = dot(oc, ray.getDirection());
    auto c = oc.lengthSquared() - m_radius * m_radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
    {
        return false;
    }

    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < min || max < root)
    {
        root = (-half_b + sqrtd) / a;
        if (root < min || max < root)
        {
            return false;
        }
    }

    record.m_t = root;
    record.m_p = ray.at(record.m_t);
    Vector3 outward_normal = (record.m_p - m_position) / m_radius;
    record.setFaceNormal(ray, outward_normal);
    record.m_material = m_material;

    return true;
}
