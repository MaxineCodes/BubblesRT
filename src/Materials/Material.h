/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	Material.h
// 
// 
//  Description:  Basic general material interface.
//				  Every material has a name variable and a scatter function.
// 				  
//				  The name variable is used to identify the material and assign it to the correct shape object when loading a scene.
//				  The scatter function is used to calculate the scattered ray after a ray hits an object, duh.
// 
//			      Every material type has its own constructor.
// 				  
// 				  
//  Types:		  Lambert:
//					A very simple material that scatters rays in a random direction and has an alebdo colour.
//					Although it is very simple, it is the basis for many other material types.
// 
//				  Phong: 
//					Basic specular material.
// 
// 			      Standard Surface: 
//					Standard PBR material.
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
	const char* m_name = "MATERIAL_DEFAULT_INTERFACE_NAME";

	virtual const char* getName() const { return m_name; };
	virtual bool scatter(const RTRay& ray, const rayHitRecord& record, colour& attenuation, Ray& scatteredRay) const = 0;
};

#include "Lambert.h"