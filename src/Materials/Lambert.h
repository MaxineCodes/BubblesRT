//
#pragma once

#include "Material.h"

class Lambert : public Material
{
public:

	Colour m_albedo;

public:

	Lambert(const Colour& albedo);

public:

	virtual bool scatter(const RTRay& ray, const rayHitRecord& record, colour& attenuation, Ray& scatteredRay) const override;

};

