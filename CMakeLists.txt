cmake_minimum_required(VERSION 3.10)

project(test)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(test test.cpp)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("${PROJECT_SOURCE_DIR}/../glfw" "${PROJECT_SOURCE_DIR}/../glfw/build")
include_directories("${PROJECT_SOURCE_DIR}/../glfw/include")
include_directories("${PROJECT_SOURCE_DIR}/lib/include")

target_link_libraries(test glfw ${GLFW_LIBRARIES})