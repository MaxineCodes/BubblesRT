/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	Math.h
//
//	Description:
//	 Some allround math functions and numbers because external libraries are scary.
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include <cmath>


//// Constant Numbers

const double pi = 3.14159265359;
const double infinity = std::numeric_limits<double>::infinity();
const double radial = cos(pi / 4);


//// Math functions

float degreesToRadians(float degrees);
float randomFloat();
float randomFloat(float min, float max);
float clamp(float value, float min, float max);