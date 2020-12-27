@echo off
pushd ..
if exist "obj" rd /s /q "obj"
if exist "bin" rd /s /q "bin"
if exist ".vs" rd /s /q ".vs"
if exist "bin\Debug-windows-x86\gamelib\gamelib.pdb" del "bin\Debug-windows-x86\gamelib\gamelib.pdb"
if exist "bin\Release-windows-x86\gamelib\gamelib.pdb" del "bin\Release-windows-x86\gamelib\gamelib.pdb"

if exist "bin\Debug-windows-x86\sandbox\sandbox.ilk" del "bin\Debug-windows-x86\sandbox\sandbox.ilk"
if exist "bin\Debug-windows-x86\sandbox\sandbox.pdb" del "bin\Debug-windows-x86\sandbox\sandbox.pdb"
if exist "bin\Release-windows-x86\sandbox\sandbox.ilk" del "bin\Release-windows-x86\sandbox\sandbox.ilk"
if exist "bin\Release-windows-x86\sandbox\sandbox.pdb" del "bin\Release-windows-x86\sandbox\sandbox.pdb"

if exist "bin\Debug-windows-x86\sandbox_world_editor\sandbox_world_editor.ilk" del "bin\Debug-windows-x86\sandbox_world_editor\sandbox_world_editor.ilk"
if exist "bin\Debug-windows-x86\sandbox_world_editor\sandbox_world_editor.pdb" del "bin\Debug-windows-x86\sandbox_world_editor\sandbox_world_editor.pdb"
if exist "bin\Release-windows-x86\sandbox_world_editor\sandbox_world_editor.ilk" del "bin\Release-windows-x86\sandbox_world_editor\sandbox_world_editor.ilk"
if exist "bin\Release-windows-x86\sandbox_world_editor\sandbox_world_editor.pdb" del "bin\Release-windows-x86\sandbox_world_editor\sandbox_world_editor.pdb"

if exist "bq_game_lib.sln" del "bq_game_lib.sln"

if exist "sandbox\sandbox.vcxproj" del "sandbox\sandbox.vcxproj"
if exist "sandbox\sandbox.vcxproj.filters" del "sandbox\sandbox.vcxproj.filters"
if exist "sandbox\sandbox.vcxproj.user" del "sandbox\sandbox.vcxproj.user"

if exist "sandbox_world_editor\sandbox_world_editor.vcxproj" del "sandbox_world_editor\sandbox_world_editor.vcxproj"
if exist "sandbox_world_editor\sandbox_world_editor.vcxproj.filters" del "sandbox_world_editor\sandbox_world_editor.vcxproj.filters"
if exist "sandbox_world_editor\sandbox_world_editor.vcxproj.user" del "sandbox_world_editor\sandbox_world_editor.vcxproj.user"
if exist "sandbox_world_editor\world.data" del "sandbox_world_editor\world.data"

if exist "gamelib\gamelib.vcxproj" del "gamelib\gamelib.vcxproj"
if exist "gamelib\gamelib.vcxproj.filters" del "gamelib\gamelib.vcxproj.filters"
if exist "gamelib\gamelib.vcxproj.user" del "gamelib\gamelib.vcxproj.user"

if exist "test\test.vcxproj" del "test\test.vcxproj"
if exist "test\test.vcxproj.filters" del "test\test.vcxproj.filters"
if exist "test\test.vcxproj.user" del "test\test.vcxproj.user"

if exist "pong\pong.vcxproj" del "pong\pong.vcxproj"
if exist "pong\pong.vcxproj.filters" del "pong\pong.vcxproj.filters"
if exist "pong\pong.vcxproj.user" del "pong\pong.vcxproj.user"

popd