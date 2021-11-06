workspace "bq_game_lib"
    architecture "x64"
    startproject "sandbox"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["SFML"] = "gamelib/deps/SFML/include"
IncludeDir["JSON"] = "gamelib/deps/JSON/"

project "gamelib"
	location "gamelib"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	pchheader "bqpch.h"
	pchsource "gamelib/source/bqpch.cpp"

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/source/**.cpp",
    }
    includedirs
	{
        "%{prj.name}/include",
		"%{IncludeDir.SFML}",
		"%{IncludeDir.JSON}"
	}

	filter "system:windows"
		systemversion "latest"
		defines{ "PLATFORM_WINDOWS" }


	
		
	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Release"


	filter "configurations:Release"
		defines "NDEBUG"
		runtime "Release"
		optimize "on"

        


project "sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/source/**.h",
		"%{prj.name}/source/**.cpp"
	}
    links
	{
        "gamelib"
	}
    includedirs
	{
        "gamelib/include",
		"%{IncludeDir.SFML}",
		"%{IncludeDir.JSON}"
	}

	filter "system:windows"
		systemversion "latest"
		defines{ "PLATFORM_WINDOWS" }

	
	filter "configurations:*"
		libdirs { "gamelib/deps/SFML/lib" }	


	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"
		links
		{	
			"sfml-graphics",
			"sfml-window",
			"sfml-system",
			"sfml-audio",
			"sfml-network"
		}
	filter "configurations:Release"
		defines "NDEBUG"
		runtime "Release"
		optimize "on"
		links
		{	
			"sfml-graphics",
			"sfml-window",
			"sfml-system",
			"sfml-audio",
			"sfml-network"
		}
project "test"
	location "test"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")
	filter "system:windows"
		systemversion "latest"
		defines{ "PLATFORM_WINDOWS" }
	filter "configurations:*"
		libdirs { "test/deps/boost/lib" }	
	links
	{
		"gamelib"
	}
	files
	{
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"gamelib/include",
		"test/deps/boost/include",
		"%{IncludeDir.SFML}"
	}
	
	
	filter "configurations:*"
		libdirs { "gamelib/deps/SFML/lib" }	

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"
		links
		{	
			"sfml-graphics",
			"sfml-window",
			"sfml-system",
			"sfml-audio",
			"sfml-network"
		}
	filter "configurations:Release"
		defines "NDEBUG"
		runtime "Release"
		optimize "on"
		links
		{	
			"sfml-graphics",
			"sfml-window",
			"sfml-system",
			"sfml-audio",
			"sfml-network"
		}


project "pong"
	location "pong"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/source/**.h",
		"%{prj.name}/source/**.cpp"
	}
	links
	{
		"gamelib"
	}
	includedirs
	{
		"gamelib/include",
		"%{IncludeDir.SFML}",
		"%{IncludeDir.JSON}"
	}

	filter "system:windows"
		systemversion "latest"
		defines{ "PLATFORM_WINDOWS" }

	
	filter "configurations:*"
		libdirs { "gamelib/deps/SFML/lib" }	
	
	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"
		links
		{	
			"sfml-graphics",
			"sfml-window",
			"sfml-system",
			"sfml-audio",
			"sfml-network"
		}
	filter "configurations:Release"
		defines "NDEBUG"
		runtime "Release"
		optimize "on"
		links
		{	
			"sfml-graphics",
			"sfml-window",
			"sfml-system",
			"sfml-audio",
			"sfml-network"
		}
	