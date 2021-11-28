cmake_minimum_required(VERSION 3.16)

project(game)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable(game ${SOURCES})

include_directories(include)

set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

if(WIN32)
	target_link_libraries(game ${CMAKE_CURRENT_SOURCE_DIR}/glfw-bin/libglfw3dll.a)
endif()

if(UNIX)
	find_package(glfw3 3.3 REQUIRED)
	find_package(OpenGL REQUIRED)

	target_include_directories(game PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include> $<INSTALL_INTERFACE:include>)
	target_link_libraries(game PUBLIC glfw OpenGL::GL ${CMAKE_DL_LIBS})
endif()