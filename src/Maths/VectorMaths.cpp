#include "VectorMaths.h"

#include "Maths.h"


// Dot product | VectorA and VectorB
float dot(const Vector3& vA, const Vector3& vB)
{
	return vA.e[0] * vB.e[0]
		 + vA.e[1] * vB.e[1]
		 + vA.e[2] * vB.e[2];
}

// Cross product | VectorA and VectorB
Vector3 cross(const Vector3& vA, const Vector3& vB)
{
	return Vector3(	vA.e[1] * vB.e[2] - vA.e[2] * vB.e[1],
					vA.e[2] * vB.e[0] - vA.e[0] * vB.e[2],
					vA.e[0] * vB.e[1] - vA.e[1] * vB.e[0]);
}

Vector3 unitVector(Vector3 vector)
{
	return vector / vector.length();
}

Vector3 randomUnitVector()
{
	return unitVector(randomUnitVectorSphere());
}

Vector3 randomUnitVectorSphere()
{
	while (true)
	{
		auto p = Vector3::random(-1, 1);
		if (p.lengthSquared() >= 1) continue;
		return p;
	}
}

Vector3 randomUnitVectorDisk()
{
	while (true)
	{
		auto p = Vector3(randomFloat(-1, 1), randomFloat(-1, 1), 0);
		if (p.lengthSquared() >= 1) continue;
		return p;
	}
}

Vector3 reflect(const Vector3& vector, const Vector3& normal)
{
	return vector - 2 * dot(vector, normal) * normal;
}

Vector3 refract(const Vector3& uv, const Vector3& normal, float etaiOverEtat)
{
	auto cos_theta = fmin(dot(-uv, normal), 1.0);
	Vector3 r_out_perp = etaiOverEtat * (uv + cos_theta * normal);
	Vector3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.lengthSquared())) * normal;
	return r_out_perp + r_out_parallel;
}
