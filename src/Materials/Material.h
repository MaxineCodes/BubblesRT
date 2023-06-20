//
#pragma once

#include "../Datatypes/Colour.h"
#include "../RTCore/RTRay.h"
#include "../RTCore/RTCollision.h"

class rayHitRecord;

class Material 
{
public:
	const char* m_name;
	virtual bool scatter(const RTRay& ray, const rayHitRecord& record, colour& attenuation, Ray& scatteredRay) const = 0;
};

#include "Lambert.h"