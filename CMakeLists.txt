cmake_minimum_required(VERSION 3.13)
# Set project name
project(erender)

# Set C++ version to 14 because sfml-audio needs auto_ptr to compile
set( CMAKE_CXX_STANDARD 14 )

# Add all files in `src` directory to SRC_LIST variable
aux_source_directory(./src/ SRC_LIST)

# Set project executable's name
add_executable(${PROJECT_NAME} ${SRC_LIST})

# Auto-update git submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# Check if submodules are available
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/SFML/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

# Set SFML variables.
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_DOC OFF)
set(SFML_BUILD_AUDIO OFF)
set(SFML_BUILD_GRAPHICS ON)
set(SFML_BUILD_WINDOW ON)
set(SFML_BUILD_NETWORK OFF)

# Compile and add SFML to project
add_subdirectory(external/SFML)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# Copy model to build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/model
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/model)
