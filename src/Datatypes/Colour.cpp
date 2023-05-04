#include "Colour.h"
#include <cmath>


Colour& Colour::operator+=(const Colour& colour)
{
    e[0] += colour.e[0];
    e[1] += colour.e[1];
    e[2] += colour.e[2];
    return *this;
}

Colour& Colour::operator*=(const float value)
{
    e[0] *= value;
    e[1] *= value;
    e[2] *= value;
    return *this;
}

// Assumes the input is between 0f-1f.
Colour Colour::convertTo255(const Colour& colour)
{
    // Multiply by 255
    float r = colour.r() * 255;
    float g = colour.g() * 255;
    float b = colour.b() * 255;
    // Round to full numbers
    r = std::round(r);
    g = std::round(g);
    b = std::round(b);

    // Return new Colour
    return Colour(r, g, b);
}

Colour operator+(const Colour& cA, const Colour& cB)
{
    return Colour(cA.e[0] + cB.e[0], cA.e[1] + cB.e[1], cA.e[2] + cB.e[2]);
}

Colour operator*(const Colour& cA, const Colour& cB)
{
    return Colour(cA.e[0] * cB.e[0], cA.e[1] * cB.e[1], cA.e[2] * cB.e[2]);
}

Colour operator*(float value, const Colour& colour)
{
    return Colour(value * colour.e[0], value * colour.e[1], value * colour.e[2]);
}

Colour operator*(const Colour& colour, float value)
{
    return value * colour;
}
