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

# Tell Qt Creator where the application executable(s) would be located on the
# device.
#
# It is not necessary to list other deployables than executables (runtime
# targets) here. The deployment process of Sailfish OS projects is opaque to
# Qt Creator and the information contained in QtCreatorDeployment.txt is only
# used to locate the executable associated with the active run configuration
# on the device in order to run it.
#
# Search the Qt Creator Manual to learn about the QtCreatorDeployment.txt file
# format.
file(WRITE "${CMAKE_BINARY_DIR}/QtCreatorDeployment.txt"
    "${CMAKE_INSTALL_PREFIX}\n${CMAKE_BINARY_DIR}/cmakesample:bin\n")
