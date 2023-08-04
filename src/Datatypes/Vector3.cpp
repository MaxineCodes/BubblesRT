#include "Vector3.h"
#include "../Maths/Maths.h"

//// Vector3 Method Declarations

// Make negative
Vector3 Vector3::operator-() const
{
	return Vector3(-e[0], -e[1], -e[2]);
}

// Index access to vector3
float Vector3::operator[](int i) const
{
	return e[i];
}
// Index access to vector3
float& Vector3::operator[](int i)
{
	return e[i];
}

// iostream stuffs
inline std::ostream& operator<<(std::ostream& out, const Vector3& v)
{
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// Add with another vector
Vector3& Vector3::operator+=(const Vector3& vector)
{
	e[0] += vector.e[0];
	e[1] += vector.e[1];
	e[2] += vector.e[2];
	return *this;
}
// Add with another vector
inline Vector3 operator+(const Vector3& u, const Vector3& v)
{
	return Vector3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// Substract with another vector
Vector3& Vector3::operator-=(const Vector3& vector)
{
	e[0] -= vector.e[0];
	e[1] -= vector.e[1];
	e[2] -= vector.e[2];
	return *this;
}
// Substract with another vector
inline Vector3 operator-(const Vector3& u, const Vector3& v)
{
	return Vector3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// Multiply vector by value
Vector3& Vector3::operator*=(const double value)
{
	e[0] *= value;
	e[1] *= value;
	e[2] *= value;
	return *this;
}
// Multiply vector by another vector
inline Vector3 operator*(const Vector3& u, const Vector3& v)
{
	return Vector3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}
// Multiply vector by value
inline Vector3 operator*(double t, const Vector3& v)
{
	return Vector3(t * v.e[0], t * v.e[1], t * v.e[2]);
}
// Multiply vector by value
inline Vector3 operator*(const Vector3& v, double t)
{
	return t * v;
}

// Divide vector by value
Vector3& Vector3::operator/=(const double value)
{
	return *this *= 1 / value;
}
// Divide vector by value
inline Vector3 operator/(Vector3 v, double t)
{
	return (1 / t) * v;
}

// Handy maths
double Vector3::length() const
{
	return std::sqrt(lengthSquared());
}
double Vector3::lengthSquared() const
{
	return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}
Vector3 Vector3::random()
{
	return Vector3(randomFloat(), randomFloat(), randomFloat());
}
Vector3 Vector3::random(float min, float max)
{
	return Vector3(randomFloat(min, max), randomFloat(min, max), randomFloat(min, max));
}
bool Vector3::nearZero() const
{
	// Return true if the vector is close to zero in all dimensions.
	const auto s = 1e-8;
	return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
}