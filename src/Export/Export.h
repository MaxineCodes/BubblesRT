/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	Export.h
//
//	Description:
//	 Contains all export functions so they can all be included together easily.
//	 Largely also to keep it simple to dig through the code.
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "../Datatypes/Image.h"

// Export as image format function definitions
extern void exportAsPPM(Image image);
extern void exportAsBMP(Image image);