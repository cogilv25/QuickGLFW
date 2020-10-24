workspace "Quick Start GLFW"
	startproject "Quick Start GLFW"

	configurations { "Debug", "Release" }
	platforms { "x86", "x64" }


project "Quick Start GLFW"
	kind "ConsoleApp"
	language "C++"

	targetdir("bin/%{cfg.platform}/%{cfg.buildcfg}")
	objdir("bin-int/%{cfg.platform}/%{cfg.buildcfg}")

	--defines "GLFW_INCLUDE_NONE"

	filter "configurations:Debug"
		defines "_DEBUG"
		symbols "On"
		linkoptions {"/NODEFAULTLIB:MSVCRT"}

	filter "configurations:Release"
		defines "_RELEASE"
		optimize "On"

	filter { "platforms:x86" }
    	system "Windows"
    	architecture "x86"

	filter { "platforms:x64" }
	    system "Windows"
	    architecture "x86_64"

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"


		postbuildcommands
		{
			("xcopy /cqeyi \"src/shaders\" \"bin/%{cfg.platform}/%{cfg.buildcfg}/shaders\""),
			("xcopy /cqeyi \"src/shaders\" \"shaders\"")
		}


	files
	{
		"src/glad.c",
		"src/**.h",
		"src/**.cpp"
	}

	includedirs	
	{
		"include"
	}

	libdirs
	{
		"lib/%{cfg.platform}"
	}

	links
	{
		"glfw3.lib",
		"opengl32.lib"
	}