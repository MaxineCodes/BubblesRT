//
#pragma once

#include "Material.h"

class Lambert : public Material
{
public:

	const char* m_name;
	Colour m_albedo;

public:

	Lambert(const Colour& albedo, const char* name = "default_name");

public:

	virtual bool scatter(const RTRay& ray, const rayHitRecord& record, colour& attenuation, Ray& scatteredRay) const override;

};

