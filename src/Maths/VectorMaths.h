#pragma once

#include "../Datatypes/Vector3.h"

inline double dot(const Vector3& u, const Vector3& v);
inline Vector3 cross(const Vector3& u, const Vector3& v);

inline Vector3 unit_vector(Vector3 v);
static Vector3 random_unit_vector();
static Vector3 random_in_unit_sphere();
static Vector3 random_in_unit_disk();

static Vector3 reflect(const Vector3& v, const Vector3& n);
static Vector3 refract(const Vector3& uv, const Vector3& n, double etai_over_etat);