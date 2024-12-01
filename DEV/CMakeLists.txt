add_executable(dev)

if(Clang-Tidy-Loc)
    message("Clang Tidy found! Enabling...\n")
    set_target_properties(dev PROPERTIES CXX_CLANG_TIDY "${Clang-Tidy-Loc}")
endif()

# If the user doesn't have cppcheck installed, but also has mingw installed, this could trigger a false positive.
# The USE_CPPCHECK variable is intended to prevent this.
if(CPP-Check-Loc AND DEV_USE_CPPCHECK)
    message("CPPCheck found! Enabling...\n")
    set_target_properties(dev PROPERTIES CXX_CPPCHECK "${CPP-Check-Loc} --project=${DEV_Compile_Database}")
endif()

if(IPO_YES)
	set_target_properties(dev PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

target_compile_options(dev PRIVATE ${CompilerFlags})
target_link_options(dev PRIVATE ${LinkerFlags})
target_compile_features(dev PUBLIC cxx_std_23)

target_compile_definitions(
	dev 
	PRIVATE 

	TGUI_THEMES="${CPM_PACKAGE_TGUI_SOURCE_DIR}/themes"
	DEV_FORMS_DIR="${DEV_Root_Dir}/config/forms"
)

target_link_libraries(
	dev 

	PRIVATE 

	SFML::Window 
	SFML::System 
	SFML::Graphics 
	TGUI::TGUI
	nlohmann_json::nlohmann_json
)

target_sources(
	dev 

	PUBLIC 

	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/App.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/MainMenu.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/Json.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/DevMenuBar.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/Query.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/internal/EventRecorder.cpp

	PUBLIC 

	FILE_SET HEADERS 

	BASE_DIRS ${CMAKE_CURRENT_LIST_DIR}/inc

	FILES

	${CMAKE_CURRENT_LIST_DIR}/inc/dev/App.hpp
	${CMAKE_CURRENT_LIST_DIR}/inc/dev/Forms.hpp
	${CMAKE_CURRENT_LIST_DIR}/inc/dev/MainMenu.hpp
	${CMAKE_CURRENT_LIST_DIR}/inc/dev/Json.hpp
	${CMAKE_CURRENT_LIST_DIR}/inc/dev/GuiPanel.hpp
	${CMAKE_CURRENT_LIST_DIR}/inc/dev/DevMenuBar.hpp
	${CMAKE_CURRENT_LIST_DIR}/inc/dev/Query.hpp
	${CMAKE_CURRENT_LIST_DIR}/inc/internal/EventRecorder.hpp

)