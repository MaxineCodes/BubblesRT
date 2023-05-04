#include "Maths.h"

float degreesToRadians(float degrees)
{
    return degrees * pi / 180.0;
}

float randomFloat()
{
    // Returns a random float between 0.0 - 0.1.
    return rand() / (RAND_MAX + 1.0);
}

float randomFloat(float min, float max)
{
    // Returns a random float between min - max
    return min + (max - min) * randomFloat();
}

float clamp(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}
