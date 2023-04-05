/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	- B U B B L E S   R A Y T R A C I N G   R E N D E R E R -
//	 ~                Offline RT renderer;                 ~
//
//	The Bubbles raytracing rendering engine is a offline raytracing engine project.
//  
//  
//	
//  
//	Description:
//  
//  
//	Credits:
//  - Maxine Meijboom
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