project "sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("%{wks.location}/build/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/build/obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"source/**.h",
		"source/**.cpp"
	}
    links
	{
        "gamelib",
        "sfml-system",
        "sfml-window",
        "sfml-graphics",
        "sfml-audio",
		"openssl-1.1/ssl",
		"openssl-1.1/crypto"
	}
    includedirs
	{
		"../../gamelib/include",
		"../../gamelib/vendor/include",
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