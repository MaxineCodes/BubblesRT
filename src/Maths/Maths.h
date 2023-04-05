#pragma once

#include <vector>
#include <cmath>

//// Constant Numbers

const double pi = 3.14159265359;
const double infinity = std::numeric_limits<double>::infinity();
const double radial = cos(pi / 4);


//// Math functions

inline float degreesToRadians(float degrees);
float randomFloat();
float randomFloat(float min, float max);
inline float clamp(float value, float min, float max);