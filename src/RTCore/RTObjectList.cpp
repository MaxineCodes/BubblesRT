#include "RTObjectList.h"

RTObjectList::RTObjectList()
{
}

RTObjectList::RTObjectList(std::shared_ptr<Shape> object)
{
}

bool RTObjectList::hit(const RTRay& ray, float min, float max, rayHitRecord& record) const
{
    rayHitRecord tmpRecord;
    bool hasIntersected = false;
    auto closest_so_far = max;

    for (const auto& object : m_objects)
    {
        if (object->intersect(ray, min, closest_so_far, tmpRecord))
        {
            hasIntersected = true;
            closest_so_far = tmpRecord.m_t;
            record = tmpRecord;
        }
    }

    return hasIntersected;
}

void RTObjectList::add(std::shared_ptr<Shape> object)
{
	m_objects.push_back(object);
}

void RTObjectList::empty()
{
}
