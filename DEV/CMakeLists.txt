add_executable(dev)

if(${CMAKE_CXX_COMPILER_ID} MATCHES MSVC)
	include("../cmake/MSVCOptions.cmake")
else()
	include("../cmake/GNUOptions.cmake")
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_YES LANGUAGES CXX C)

if(IPO_YES)
	set_target_properties(dev PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

target_compile_options(dev PRIVATE ${CompilerFlags})
target_link_options(dev PRIVATE ${LinkerFlags})

target_include_directories(
	dev 

	PUBLIC 

	${CMAKE_CURRENT_LIST_DIR}/inc
)

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

	${CMAKE_CURRENT_LIST_DIR}/inc/App.h

	PRIVATE 

	${CMAKE_CURRENT_LIST_DIR}/src/App.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
)