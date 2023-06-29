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
IncludeDir["SFML"] = "/usr/include/SFML/"
IncludeDir["BOOST"] ="/usr/include/boost"

group "Core"
	include "gamelib"
	include "tests"
group ""
group "Demos"
	include "demos/sandbox"
	include "demos/chess_engine"
group ""



