-- premake5.lua
workspace "BubblesRT"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "BubblesApp"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
	include "BubblesCore/Build-Core.lua"
group ""

include "BubblesApp/Build-App.lua"