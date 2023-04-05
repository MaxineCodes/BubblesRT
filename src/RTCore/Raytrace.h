#pragma once

#include "../Datatypes/Image.h"
#include "../Datatypes/Colour.h"
#include "RTSettings.h"
#include "RTScene.h"

// Raytracing start
Image Raytrace(
	const RTSettings& settings,
	const RTScene& scene,
	int sampleCount
);