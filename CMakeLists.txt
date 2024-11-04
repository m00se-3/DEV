cmake_minimum_required(VERSION 3.28)

project(DataEditorViewer LANGUAGES CXX)

include(CPM.cmake)

# Search for ccache, clang-tidy

find_program(Clang-Tidy-Loc clang-tidy)
find_program(CPP-Check-Loc cppcheck)
find_program(CCache-Loc ccache)

if(CCache-Loc)
    message("ccache found! Enabling...\n")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCache-Loc})
    set(CPM_SOURCE_CACHE ${CMAKE_CURRENT_LIST_DIR}/.cache/CPM)
endif()

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
cpmaddpackage("gh:gsl-lite/gsl-lite@0.41.0")

add_subdirectory("DEV")