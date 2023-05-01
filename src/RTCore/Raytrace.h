/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	Raytrace.h
// 
//	(Finally the good stuff)
// 
//>------------------------------------------------------------------------------------------
// 
//  Description:  Where the magic happens! This is essentially where the RT algorithm starts.
//				  Generates an image from the 3D data it is provided.
// 				  
//				  This raytracer is not particularely efficient or feature-rich.
//				  It is a learning exersize after all. :) 
// 				  
// 				  
//  Usage:		  Call "raytrace()" and it will return an image. Very complicated yesyes.
// 				  
// 				  
//	Input:		  RTSettings: Provides a bunch of raytracing settings, such as image size, 
//				  render scale, debug settings, etc.
// 				  
//				  RTScene: Provides the scene data, such as objects, their materials, lights,
//				  camera, skybox, etc. 
//				  
//				  sampleCount: Just an integer value for the sample count per pixel, duhh.
// 
//>------------------------------------------------------------------------------------------
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "../Datatypes/Image.h"
#include "../Datatypes/Colour.h"
#include "RTSettings.h"
#include "RTScene.h"
#include "RTRay.h"

// Raytracing Start
Image raytrace(
	RTSettings& settings,
	RTScene& scene,
	const int sampleCount
);

// Print functions
void printRTSettings(RTSettings& settings, const int sampleCount);
void printRTSceneInfo(RTScene& scene);