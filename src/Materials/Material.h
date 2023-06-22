/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	Material.h
//
//	Description:
//	 Basic general material interface.
//   Every material has a name variable and a scatter function.
// 
//   The name variable is used to identify the material type and assign it to the correct shape object when loading a scene.
//   The scatter function is used to calculate the scattered ray after a ray hits an object, duh.
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
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