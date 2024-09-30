add_executable(dev)

if(${CMAKE_CXX_COMPILER_ID} MATCHES MSVC)
	include("../cmake/MSVCOptions.cmake")
else()
	include("../cmake/GNUOptions.cmake")
endif()

target_compile_options(dev PRIVATE ${CompilerFlags})
target_link_options(dev PRIVATE ${LinkerFlags})

target_link_libraries(
	dev 

	PRIVATE 

	SFML::Window 
	SFML::System 
	SFML::Graphics 
	gsl::gsl-lite 
	TGUI
)

target_sources(
	dev 

	PRIVATE 

	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
)