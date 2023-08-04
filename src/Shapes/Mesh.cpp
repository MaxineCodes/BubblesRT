#include "Mesh.h"

Mesh::Mesh(const char* name)
{
	m_name = name;
}

bool Mesh::intersect(const RTRay& ray, float min, float max, rayHitRecord& record) const
{
	// If any of the polygons are intersected
	for (int i = 0; i < m_polygons.size(); i++)
	{
		if (m_polygons[i].get()->intersect(ray, min, max, record))
		{
			return true;
		}
	}

	return false;
}
