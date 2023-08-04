/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	Lambert.h
//
//	Description:
//	 A very simple material that scatters rays in a random direction and has an alebdo colour.
//   Although it is very simple, it is the basis for many other material types.
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Material.h"


class Lambert : public Material
{
public:
	const char* m_name = "LAMBERT_DEFAULT_NAME";
	Colour m_albedo;

	Lambert(const Colour& albedo, const char* name = "LAMBERT_DEFAULT_NAME");

	const char* getName() const override { return m_name; };
	bool scatter(const RTRay& ray, const rayHitRecord& record, colour& attenuation, Ray& scatteredRay) const override;
};

