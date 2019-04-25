project(cmakesample CXX)
cmake_minimum_required(VERSION 3.5)

# For the example we assume to always be compiling for SailfishOS.
option(SAILFISHOS "set SailfishOS target" ON)
option(SAILFISHAPP "Use libsailfishapp features" ON)

find_package (Qt5 COMPONENTS Core Network Qml Gui Quick REQUIRED)

if(SAILFISHOS)
    include(FindPkgConfig)
    if(SAILFISHAPP)
        pkg_search_module(SAILFISH sailfishapp REQUIRED)
        add_definitions(-DSAILFISHAPP)
    else()
        pkg_search_module(BOOSTER_MODULE qdeclarativecache5-boostable)
        if(BOOSTER_MODULE)
            message("Compiling with qdeclarative5-boostable support.")
            add_definitions(-DHAS_BOOSTER)
        else()
            message(WARNING "qdeclarative5-boostable not available; startup times will be slower.")
        endif()
    endif()
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(cmakesample main.cpp)
if (SAILFISHOS)
    target_include_directories(cmakesample PRIVATE
        $<BUILD_INTERFACE:
        ${SAILFISH_INCLUDE_DIRS}
    >)
    target_link_libraries(cmakesample
        Qt5::Quick
        ${SAILFISH_LDFLAGS}
    )
else()
    target_link_libraries(cmakesample
        Qt5::Quick
    )
endif()

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
