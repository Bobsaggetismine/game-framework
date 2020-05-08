pushd .. 
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvars32.bat"
msbuild bq_game_lib.sln /p:Configuration=Debug /p:Platform="x64"