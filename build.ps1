param([string]$BuildType="Release")

cmake -E make_directory $PSScriptRoot/build
Set-Location $PSScriptRoot/build
cmake -G "Visual Studio 15 2017" -A x64 -T host=x86 .. "-DCMAKE_BUILD_TYPE=$BuildType"
cmake --build . --config $BuildType
Set-Location $PSScriptRoot