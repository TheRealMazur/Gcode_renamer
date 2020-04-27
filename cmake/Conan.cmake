macro(run_conan)
# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(
    STATUS
      "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
       "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_add_remote(NAME bincrafters URL
                 https://api.bintray.com/conan/bincrafters/public-conan)

if(ENV{CC} MATCHES " " OR ENV{CXX} MATCHES " ")
  set(COMPILER_PATH_HAS_SPACES) # conan doesn't escape spaces inside some variables, so we unset them and let qmake find the values
endif()



if(COMPILER_PATH_HAS_SPACES) 
  set(TEMP_CC $ENV{CC}) 
  set(TEMP_CXX $ENV{CXX})
  unset(ENV{CC})
  unset(ENV{CXX})
endif(COMPILER_PATH_HAS_SPACES)

conan_cmake_run(
  CONANFILE conanfile.txt
  BASIC_SETUP
  TARGETS 
  CMAKE_TARGETS # individual targets to link to
  BUILD
  missing)

if(COMPILER_PATH_HAS_SPACES) 
  set(CC $ENV{TEMP_CC})
  set(CXX $ENV{TEMP_CXX})
  unset(ENV{TEMP_CC})
  unset(ENV{TEMP_CXX})
endif(COMPILER_PATH_HAS_SPACES)
  
endmacro()
