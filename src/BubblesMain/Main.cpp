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


// Entrypoint (Duh)
int main(void)
{
    const int ImageWidth  = 640;
    const int ImageHeight = 480;

    // Get Raytrace settings
    RTSettings raytraceSettings(ImageWidth, ImageHeight);

    // Get scene
    RTScene raytraceScene;

    // Generated Raytraced Image
    Image RTOutput = Raytrace(
        raytraceSettings,   // RTSettings
        raytraceScene,      // RTScene
        10                  // Sample Count
    );

    // Initialize the window
    const char* windowName = "BubblesRT";
    OpenglWindow viewportWindow = OpenglWindow(windowName, raytraceSettings.ImageWidth, raytraceSettings.ImageHeight);

    // Display Raytraced Image
    viewportWindow.ClearWindow(Colour::Cyan());
    viewportWindow.DrawImage(RTOutput);
}