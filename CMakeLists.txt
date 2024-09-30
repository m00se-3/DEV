cmake_minimum_required(VERSION 3.25)

project(DataEditorViewer LANGUAGES CXX)

include(CPM.cmake)

# Search for ccache, clang-tidy

find_program(Clang-Tidy-Loc clang-tidy)
find_program(CPP-Check-Loc cppcheck)
find_program(CCache-Loc ccache)

if(Clang-Tidy-Loc)
    message("Clang Tidy found! Enabling...\n")
    set(CMAKE_CXX_CLANG_TIDY ${Clang-Tidy-Loc})
elseif(CPP-Check-Loc)
    message("CPPCheck found! Enabling...\n")
    set(CMAKE_CXX_CPPCHECK ${CPP-Check-Loc})
endif()

if(CCache-Loc)
    message("ccache found! Enabling...\n")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCache-Loc})
endif()

# Install dependencies

cpmaddpackage("gh:SFML/SFML#3.0.0-rc.1")
cpmaddpackage("gh:gsl-lite/gsl-lite@0.41.0")
cpmaddpackage(
    Name TGUI 
    GITHUB_REPOSITORY texus/TGUI 
    VERSION 1.5.0
    OPTIONS "TGUI_BACKEND SFML_GRAPHICS"
)

add_subdirectory("DEV")