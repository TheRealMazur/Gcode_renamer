cmake_minimum_required(VERSION 3.16)

# Set the project name
project(Gcode_renamer CXX)

include(cmake/StandardProjectSettings.cmake)

# Force an out-of-source build of the code by default
option(FORCE_OUT_OF_SOURCE_BUILD "Force out-of-source build" ON)
if(FORCE_OUT_OF_SOURCE_BUILD)
  include(cmake/MacroOutOfSourceBuild.cmake)
  string(CONCAT MSG "${PROJECT_NAME} by default enforces an out of source build.\n" ;
                "You can disable this by setting FORCE_OUT_OF_SOURCE_BUILD to OFF.\n")
  macro_ensure_out_of_source_build(${MSG})
endif()

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_TESTING "Enable Test Builds" OFF)

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if(ENABLE_PCH)
  # This sets a global PCH parameter, each project will build its own PCH, which is a good idea if any #define's change
  #
  target_precompile_headers(project_options INTERFACE <vector> <string> <map> <utility>)
endif()

# Set up some extra Conan dependencies based on our needs before loading Conan
set(CONAN_EXTRA_REQUIRES
"qt/5.14.1@bincrafters/stable")
set(CONAN_EXTRA_OPTIONS
Qt:shared=False
Qt:commercial=False
Qt:opengl=desktop
Qt:openssl=False
Qt:with_pcre2=False
Qt:with_glib=False
# Qt:with_doubleconversion=False
Qt:with_freetype=False
Qt:with_fontconfig=False
Qt:with_icu=False
Qt:with_harfbuzz=False
Qt:with_libjpeg=False
Qt:with_libpng=False
Qt:with_sqlite3=False
Qt:with_mysql=False
Qt:with_pq=False
Qt:with_odbc=False
Qt:with_sdl2=False
Qt:with_libalsa=False
Qt:with_openal=False
Qt:with_zstd=False
Qt:GUI=True
Qt:widgets=True
Qt:device=None
Qt:cross_compile=None
Qt:sysroot=None
Qt:config=None
# Qt:multiconfiguration=True # Uncomment this to build both debug and release versions of Qt
)

include(cmake/Conan.cmake)
run_conan()

include_directories(src)

if(ENABLE_TESTING)
  enable_testing()
  message("Building Tests.")
  add_subdirectory(test)
endif()

add_subdirectory(src)
