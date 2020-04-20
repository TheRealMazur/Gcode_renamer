set(BINARY ${CMAKE_PROJECT_NAME})
find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(
  GLOB_RECURSE SOURCES
  LIST_DIRECTORIES true
  *.h *.cpp *.ui *.qrc)

set(SOURCES ${SOURCES})

add_executable(${BINARY} WIN32 ${SOURCES})

install(TARGETS ${BINARY} RUNTIME DESTINATION .)

target_link_libraries(
  ${BINARY}
  PRIVATE project_warnings project_options
  PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets)
target_include_directories(${BINARY} PRIVATE ${CONAN_INCLUDE_DIRS_QT})
