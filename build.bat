@echo off
setlocal

set BUILD_DIR="build"
set BUILD_TYPE="Debug"

if %CLEAN_BUILD%==true (
  rmdir /s /q %BUILD_DIR%
  mkdir %BUILD_DIR%
)

if not exist %BUILD_DIR% mkdir %BUILD_DIR%

pushd %BUILD_DIR%

conan profile detect --force
conan install .. --output-folder=. --build=missing --settings=build_type=%BUILD_TYPE%

cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
cmake --build .

DOOM_STYLE.exe

popd

endlocal
