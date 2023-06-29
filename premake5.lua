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
IncludeDir["SFML_LINUX"] = "/usr/include/SFML/"
IncludeDir["BOOST_LINUX"] ="/usr/include/boost"
IncludeDir["JSON"] = "gamelib/deps/JSON/"

project "gamelib"
	location "gamelib"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/obj/" .. outputdir .. "/%{prj.name}")

	pchheader "gamelib/include/bqpch.h"
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
	filter "system:linux"
		systemversion "latest"
		defines{ "PLATFORM_LINUX" }
		
	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"


	filter "configurations:Release"
		defines "NDEBUG"
		runtime "Release"
		optimize "on"

        


project "sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/source/**.h",
		"%{prj.name}/source/**.cpp"
	}
    links
	{
        "gamelib",
        "sfml-system",
        "sfml-window",
        "sfml-graphics",
        "sfml-audio",
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
	filter "system:linux"
		systemversion "latest"
		defines{ "PLATFORM_LINUX" }
		
	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "NDEBUG"
		runtime "Release"
		optimize "on"

project "test"
	location "test"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/obj/" .. outputdir .. "/%{prj.name}")

	links
	{
		"boost_unit_test_framework",
		"gamelib",
		"sfml-graphics",
		"sfml-window",
		"sfml-system",
		"sfml-audio",
		"sfml-network",
	}
	
	files
	{
		"%{prj.name}/src/**.cpp",
    }

    includedirs
	{
		"gamelib/include",
		"%{IncludeDir.BOOST}",
	}

	filter "system:windows"
		systemversion "latest"
		defines{ "PLATFORM_WINDOWS" }

	filter "system:linux"
		systemversion "latest"
		defines{ "PLATFORM_LINUX" }

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "NDEBUG"
		runtime "Release"
		optimize "on"


project "chess_engine"
	location "chess_engine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/source/**.h",
		"%{prj.name}/source/**.hpp",
		"%{prj.name}/source/**.cpp",
		"%{prj.name}/source/surge/**.h",
		"%{prj.name}/source/surge/**.hpp",
		"%{prj.name}/source/surge/**.cpp"
	}
	links
	{
		"gamelib",
		"sfml-graphics",
		"sfml-window",
		"sfml-system",
		"sfml-audio",
		"sfml-network"
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
	filter "system:linux"
		systemversion "latest"
		defines{ "PLATFORM_LINUX" }
	
	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "NDEBUG"
		runtime "Release"
		optimize "on"