cmake_minimum_required(VERSION 3.13)
project(erender)

set( CMAKE_CXX_STANDARD 17 )

aux_source_directory(./src/ SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

add_subdirectory(external/SFML)
target_include_directories(${PROJECT_NAME} PUBLIC external/SFML/include)
target_link_directories(${PROJECT_NAME} PUBLIC external/SFML/lib)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
