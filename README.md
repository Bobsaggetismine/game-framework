
# game-framework

Application framework for developing 2d or console c++ applications




## Building, Running, Tests

prerequisites: 

premake5 installed

Tests require boost to be installed (and if you're on windows or have it installed in a non standard path you'll have to edit the premake5.lua script to point it to your boost location)

All projects require sfml is installed and again, in a standard path (or editing of the premake5.lua script)

Once you have these steps done, enter the command: premake5 <your prefered build> (options are gmake, vs2022, xcode)

after this you can simply either open the generated build/project files in an ide or if you use make, do: make config=release or make config=debug

navigate to build/bin/<platform/config>/<project> and run the executable (Note: Some projects have required res folders in their project folder that need to be copied to run properly such as textures, fonts, ect)