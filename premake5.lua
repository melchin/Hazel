workspace "Hazel" -- Solution Name
    architecture "x64"
    startproject "Sandbox" -- When we Right Click Sandbox Project and select "Set as Startup Project"
    -- startup project is stored in .vs so this might have to manually set the startup project unless this folder gets deleted.

    configurations
    {
        "Debug", -- No optimizations applied
        "Release", -- Like Debug, with less Debug abilities and more optimizations (includes logging)
        "Dist" -- Logging stript, this is what you release to the public
    }

-- List of macros (tokens) found here: https://github.com/premake/premake-core/wiki/Tokens
-- cfg.buildcfg - Debug or Release
-- cfg.system - Windows, Mac, etc.
-- cfg.architecture - x64, x86, etc.
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include"
IncludeDir["Glad"] = "Hazel/vendor/Glad/include"

include "Hazel/vendor/GLFW" -- Includes the premake5.lua file that we created in our Fork of GLFW
include "Hazel/vendor/Glad" -- Includes the premake5.lua file that we created in our copy of Glad

project "Hazel"
    location "Hazel" -- So we can reference from Hazel project and not from solution directory
    kind "SharedLib" -- Type of file that this is (DLL)
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "hzpch.h" -- <Project> -> Properties -> C/C++ -> Precompiled Headers
    pchsource "Hazel/src/hzpch.cpp"

    files 
    {
        "%{prj.name}/src/**.h", -- Where to find the files for this project. Double ** searches children within that path.
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        -- $(SolutionDir)Hazel\vendor\spdlog\include; From VS 
        -- <Project> -> Properties -> C/C++ -> General -> Additional Include Directories
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}"
    }

    links
    {
        "GLFW", -- Hazel is dependant on GLFW. Hazel References GLFW
        "Glad", -- Hazel is dependant on Glad. Hazel References Glad
        "opengl32.lib" -- Hazel is dependant on opengl32.lib
    }

    filter "system:windows" -- Project Configuration for Windows platform specifically
        cppdialect "C++17" -- <Project> -> Properties -> General -> C++ Language Standard
        staticruntime "On" -- Linking the runtime libraries
        systemversion "latest" -- Can find specific version at <Project> -> Properties -> General -> Windows SDK Version

        defines -- <Project> -> Properties -> C/C++ -> Preprocessor -> Preprocessor Definitions
        {
            "HZ_PLATFORM_WINDOWS",
            "HZ_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }
         
        postbuildcommands --https://github.com/premake/premake-core/wiki/postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox") -- Copies Hazel DLL's to Sandbox so that Sandbox can access it.
        }
    
    filter "configurations:Debug"
         defines "HZ_DEBUG"
         buildoptions "/MDd"
         symbols "On"
    
    filter "configurations:Release"
         defines "HZ_RELEASE"
         buildoptions "/MD"
         optimize "On"

    filter "configurations:Dist"
         defines "HZ_DIST"
         buildoptions "/MD"
         optimize "On"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp" -- Type of file that this is (exe)
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Hazel/vendor/spdlog/include",
		"Hazel/src"
	}

	links
	{
		"Hazel" -- Sandbox is dependant on Hazel. Sandbox References Hazel
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0"

		defines
		{
			"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
        buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
        buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
        buildoptions "/MD"
		optimize "On" 