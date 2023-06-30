project "tests"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("%{wks.location}/build/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/build/obj/" .. outputdir .. "/%{prj.name}")

	links
	{
		"boost_unit_test_framework",
		"gamelib",
		"sfml-graphics",
		"sfml-window",
		"sfml-system",
		"sfml-audio",
		"sfml-network",
		"openssl-1.1/ssl",
		"openssl-1.1/crypto"
	}
	
	files
	{
		"source/**.cpp",
    }

    includedirs
	{
		"../gamelib/include",
		"../gamelib/vendor/include",
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