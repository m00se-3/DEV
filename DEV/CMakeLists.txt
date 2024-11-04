add_executable(dev)

if(Clang-Tidy-Loc)
    message("Clang Tidy found! Enabling...\n")
    set_property(TARGET dev PROPERTY CXX_CLANG_TIDY ${Clang-Tidy-Loc})
elseif(CPP-Check-Loc)
    message("CPPCheck found! Enabling...\n")
    set_property(TARGET dev PROPERTY CXX_CPPCHECK ${CPP-Check-Loc})
endif()

if(${CMAKE_CXX_COMPILER_ID} MATCHES MSVC)
	include("../cmake/MSVCOptions.cmake")
else()
	include("../cmake/GNUOptions.cmake")
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_YES LANGUAGES CXX)

if(IPO_YES)
	set_target_properties(dev PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

target_compile_options(dev PRIVATE ${CompilerFlags})
target_link_options(dev PRIVATE ${LinkerFlags})
target_compile_features(dev PUBLIC cxx_std_23)
target_compile_definitions(dev PRIVATE TGUI_THEMES="${CPM_PACKAGE_TGUI_SOURCE_DIR}/themes")

target_link_libraries(
	dev 

	PRIVATE 

	SFML::Window 
	SFML::System 
	SFML::Graphics 
	gsl::gsl-lite 
	TGUI::TGUI
)

target_sources(
	dev 

	PUBLIC 

	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/App.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/MainMenu.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/Json.cpp

	PUBLIC 

	FILE_SET HEADERS 

	BASE_DIRS ${CMAKE_CURRENT_LIST_DIR}/inc

	FILES

	${CMAKE_CURRENT_LIST_DIR}/inc/dev/App.hpp
	${CMAKE_CURRENT_LIST_DIR}/inc/dev/Forms.hpp
	${CMAKE_CURRENT_LIST_DIR}/inc/dev/MainMenu.hpp
	${CMAKE_CURRENT_LIST_DIR}/inc/dev/Json.hpp

)