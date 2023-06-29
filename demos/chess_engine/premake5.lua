project "chess_engine"
	location "demos/chess_engine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("%{wks.location}/build/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/build/obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"source/**.h",
		"source/**.hpp",
		"source/**.cpp",
		"source/surge/**.h",
		"source/surge/**.hpp",
		"source/surge/**.cpp"
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
		"../../gamelib/include",
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