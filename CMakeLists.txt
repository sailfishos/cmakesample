project(cmakesample CXX)
cmake_minimum_required(VERSION 2.8.11)

find_package(Qt5Qml REQUIRED)

include(FindPkgConfig)
pkg_search_module(SAILFISH sailfishapp REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(cmakesample main.cpp)
set_property(TARGET cmakesample
  PROPERTY INCLUDE_DIRECTORIES
  INCLUDE_DIRECTORIES "${SAILFISH_INCLUDE_DIRS}")
qt5_use_modules(cmakesample Qml)
target_link_libraries(cmakesample ${SAILFISH_LDFLAGS})

install(TARGETS cmakesample
RUNTIME DESTINATION bin)

install(DIRECTORY qml
DESTINATION share/cmakesample)

install(DIRECTORY translations
DESTINATION share/cmakesample
FILES_MATCHING PATTERN "*.qm")

install(FILES cmakesample.desktop
DESTINATION share/applications)

install(FILES cmakesample.png
DESTINATION share/icons/hicolor/86x86/apps)
