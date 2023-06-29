project "gamelib"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("%{wks.location}/build/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/build/obj/" .. outputdir .. "/%{prj.name}")

	pchheader "gamelib/include/bqpch.h"
	pchsource "gamelib/source/bqpch.cpp"

	files
	{
		"include/**.h",
		"source/**.cpp",
    }
	includedirs
	{
		"include",
		"%{IncludeDir.SFML}",
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