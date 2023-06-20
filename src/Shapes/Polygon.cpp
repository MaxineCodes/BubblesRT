#include "Polygon.h"

Polygon::Polygon(Vertex vertexA, Vertex vertexB, Vertex vertexC) 
	: vertexA(vertexA), vertexB(vertexB), vertexC(vertexC)
{
	std::cout << "Constructing Polygon" << std::endl;
}

bool Polygon::intersect(const RTRay& ray, float min, float max, rayHitRecord& record)
{
	return false;
}
