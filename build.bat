@echo off
setlocal
set BUILD_DIR=build
mkdir %BUILD_DIR%
cd %BUILD_DIR%
cmake ..
cmake --build . --config Release
cd ..
pause