#include "Polygon.h"

Polygon::Polygon(Vertex vertexA, Vertex vertexB, Vertex vertexC) 
	: vertexA(vertexA), vertexB(vertexB), vertexC(vertexC)
{
	std::cout << "Constructing Polygon" << std::endl;
}

bool Polygon::intersect(const RTRay& ray, float min, float max, rayHitRecord& record) const
{
	std::cout << "Polygon intersection not implemented yet" << std::endl;
	//record.m_t = root;
	//record.m_p = ray.at(record.m_t);
	//Vector3 outward_normal = (record.m_p - m_position) / m_radius;
	//record.setFaceNormal(ray, outward_normal);
	//record.m_material = m_material;
	return false;
}
