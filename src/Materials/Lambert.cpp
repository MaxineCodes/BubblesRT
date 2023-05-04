#include "Lambert.h"

Lambert::Lambert(const Colour& albedo)
{
	m_albedo = albedo;
}

bool Lambert::scatter(const RTRay& ray, const rayHitRecord& record, colour& attenuation, Ray& scatteredRay) const
{
    Vector3 scatter_direction = record.m_normal + randomUnitVector();

    // Catch degenerate scatter direction
    if (scatter_direction.nearZero())
    {
        scatter_direction = record.m_normal;
    }

    scatteredRay = RTRay(record.m_p, scatter_direction);
    attenuation = m_albedo;
    return true;
}
