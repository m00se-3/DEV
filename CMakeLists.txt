cmake_minimum_required(VERSION 3.28)

project(DataEditorViewer LANGUAGES CXX)

include(CTest)
include(CPM.cmake)
include(cmake/Config.cmake)

if(CCache-Loc)
    message("ccache found! Enabling...\n")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCache-Loc})
    set(CPM_SOURCE_CACHE ${CMAKE_CURRENT_LIST_DIR}/.cache/CPM)
    file(WRITE ${CPM_SOURCE_CACHE}/.clang-tidy "Checks: -*")
endif()

set(DEV_Compile_Database ${CMAKE_CURRENT_LIST_DIR}/compil_commands.json)
set(DEV_Root_Dir ${CMAKE_CURRENT_LIST_DIR})

# Install dependencies

cpmaddpackage(
    NAME SFML 
    GITHUB_REPOSITORY SFML/SFML 
    GIT_TAG 3.0.0-rc.1
    OPTIONS "BUILD_SHARED_LIBS OFF"
)

cpmaddpackage(
    Name TGUI 
    GITHUB_REPOSITORY texus/TGUI 
    VERSION 1.6.1
    OPTIONS 
    "BUILD_SHARED_LIBS OFF"
    "TGUI_STATIC_LIBRARIES TRUE"
    "TGUI_BACKEND SFML_GRAPHICS"
    "SFML_DIR ${CPM_PACKAGE_SFML_BINARY_DIR}"
    "SFML_STATIC_LIBRARIES ON"
)

cpmaddpackage("gh:nlohmann/json@3.11.3")
cpmaddpackage("gh:doctest/doctest@2.4.11")

add_subdirectory("DEV")
add_subdirectory("tests")