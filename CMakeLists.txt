cmake_minimum_required(VERSION 3.10)

project(lucidity)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(lucidity 
			   src/lucidity.cpp 
			   src/shader.cpp 
			   src/game.cpp 
			   src/globals.cpp
			   src/stb_image.cpp
			   src/camera.cpp
			   src/sprite.cpp
			   src/map.cpp)

# set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set_target_properties(lucidity PROPERTIES COMPILE_FLAGS "-std=c++17  -O3 -fexceptions")
set_target_properties(lucidity PROPERTIES LINK_FLAGS "
						-std=c++17 
						-O3
						-flto 
						-s ASSERTIONS=1
						
						-s USE_GLFW=3 
						-s MAX_WEBGL_VERSION=2 
						-s MIN_WEBGL_VERSION=2 
						-s WASM=1
						-s TOTAL_MEMORY=256MB 
						
						-s ENVIRONMENT=web,worker
						--bind
						--preload-file ../shaders 
						--preload-file ../src/images")
# add_subdirectory("${PROJECT_SOURCE_DIR}/../glfw" "${PROJECT_SOURCE_DIR}/../glfw/build")
add_subdirectory("${PROJECT_SOURCE_DIR}/lib" "${PROJECT_SOURCE_DIR}/lib/build")
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/glm" "${PROJECT_SOURCE_DIR}/lib/glm/build")

# include_directories("${PROJECT_SOURCE_DIR}/../glfw/include")
include_directories("${PROJECT_SOURCE_DIR}/lib/include")
include_directories("${PROJECT_SOURCE_DIR}/lib/glm")

# target_link_libraries(lucidity glfw ${GLFW_LIBRARIES})
# target_link_libraries(lucidity glfw)
# target_link_libraries(lucidity glad)
target_link_libraries(lucidity glm)

# find_package(GLUT REQUIRED)
# include_directories(${GLUT_INCLUDE_DIR})
# target_link_libraries(lucidity GL)
# target_link_libraries(lucidity glut)
# find_package(GLEW REQUIRED)
# target_link_libraries(lucidity GLEW::GLEW)