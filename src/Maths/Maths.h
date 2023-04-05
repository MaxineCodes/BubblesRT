#pragma once

#include <vector>
#include <cmath>

//// Constant Numbers

const double pi = 3.14159265359;
const double infinity = std::numeric_limits<double>::infinity();
const double radial = cos(pi / 4);


//// Math functions

inline float degreesToRadians(float degrees);

// Returns a random float between 0.0 - 0.1.
static float randomFloat();
// Returns a random float between min - max
static float randomFloat(float min, float max);

inline float clamp(float value, float min, float max);