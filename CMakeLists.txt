cmake_minimum_required(VERSION 3.13)
project(erender)

set( CMAKE_CXX_STANDARD 17 )

aux_source_directory(./src/ SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
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

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/SFML/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(external/SFML)
target_include_directories(${PROJECT_NAME} PUBLIC external/SFML/include)
target_link_directories(${PROJECT_NAME} PUBLIC external/SFML/lib)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
