project(cmakesample CXX)
cmake_minimum_required(VERSION 3.5)

find_package (Qt5 COMPONENTS Core Network Qml Gui Quick REQUIRED)

include(FindPkgConfig)
pkg_search_module(SAILFISH sailfishapp REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(cmakesample main.cpp)
target_include_directories(cmakesample PRIVATE
    $<BUILD_INTERFACE:
    ${SAILFISH_INCLUDE_DIRS}
>)
target_link_libraries(cmakesample
    Qt5::Quick
    ${SAILFISH_LDFLAGS}
)

install(TARGETS cmakesample
    RUNTIME DESTINATION bin
)
install(DIRECTORY qml
    DESTINATION share/cmakesample
)
install(DIRECTORY translations
    DESTINATION share/cmakesample
    FILES_MATCHING PATTERN "*.qm"
)
install(FILES cmakesample.desktop
    DESTINATION share/applications
)
install(FILES cmakesample.png
    DESTINATION share/icons/hicolor/86x86/apps
)
