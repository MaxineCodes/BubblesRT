#include "Colour.h"
#include <cmath>

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