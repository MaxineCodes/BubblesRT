#include "RTRay.h"

Vector3 RTRay::getOrigin() const
{
    return m_origin;
}

Vector3 RTRay::getDirection() const
{
    return m_direction;
}

Vector3 RTRay::at(float t) const
{
    return m_origin + t * m_direction;
}
