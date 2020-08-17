mkdir build
cd build
cmake ..
msbuild Logger.sln /p:Configuration=Release
msbuild Logger.sln /p:Configuration=Debug
pause
