/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	- B U B B L E S   R A Y T R A C I N G   R E N D E R E R -
//	 ~                Offline RT renderer;                 ~
//
//	The Bubbles raytracing rendering engine is a offline/CPU raytracing engine project.
// 
//>------------------------------------------------------------------------------------------
// 
//  Description:  The goal of this project is to stay away from external libraries,
//                and really understand how raytracing works under the hood. 
// 
//                This raytracer is not particularely efficient or feature-rich.
//                It is a learning exersize after all. :) 
// 
// 
//  Usage:        Currently everything is simply thrown into the main() function.
// 
// 
//  Dependencies: *OpenGL
//                *GLEW
//                *GLFW
//	
//  Further Info: The Github Wiki Pages will have more explanation on how this mess works.
//                The Github Readme contains some simple progress updates.
// 
//>------------------------------------------------------------------------------------------
//  
//  Starting date: 04/04/2023 
//  
//	Credits: Maxine Meijboom
//           [github.com/MaxineCodes]
//           [linkedin.com/in/maxinemeijboom]
//  
/////////////////////////////////////////////////////////////////////////////////////////////

// Includes
#include "../Window/OpenglWindow.h"
#include "../RTCore/Raytrace.h"
#include "../Export/Export.h"

// Entrypoint (Duh)
int main(void)
{
    const int ImageWidth  = 640;
    const int ImageHeight = 640;
    const int samepleCount = 1;

    // Get Raytrace Settings
    RTSettings raytraceSettings(ImageWidth, ImageHeight);

    // Get Scene
    std::string raytraceScenepath = "";
    RTScene raytraceScene(raytraceScenepath);

    raytraceSettings.printInfo(samepleCount);
    raytraceScene.printInfo();

    // Generate a raytraced image
    Image RTOutput = raytrace(
        raytraceSettings,   // RTSettings
        raytraceScene,      // RTScene
        samepleCount        // Sample Count
    );

    // Export raytraced image to disk
    //exportAsPPM(RTOutput);

    // Initialize Opengl window and give it the output raytraced image to render
    //const char* windowName = "BubblesRT";
    //OpenglWindow viewportWindow = OpenglWindow(windowName, RTOutput);
}