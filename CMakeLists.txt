cmake_minimum_required(VERSION 3.10)

project(lucidity)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(lucidity 
			   src/lucidity.cpp 
			   src/shader.cpp 
			   src/renderer.cpp 
			   src/globals.cpp)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("${PROJECT_SOURCE_DIR}/../glfw" "${PROJECT_SOURCE_DIR}/../glfw/build")
add_subdirectory("${PROJECT_SOURCE_DIR}/lib" "${PROJECT_SOURCE_DIR}/lib/build")
include_directories("${PROJECT_SOURCE_DIR}/../glfw/include")
include_directories("${PROJECT_SOURCE_DIR}/lib/include")

target_link_libraries(lucidity glfw ${GLFW_LIBRARIES})
target_link_libraries(lucidity glad)