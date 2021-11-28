cmake_minimum_required(VERSION 3.20)

project(jogoDrole)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable(game ${SOURCES})

include_directories(include)

set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

if(WIN32)
	target_link_libraries(game ${CMAKE_CURRENT_SOURCE_DIR}/glfw-bin/libglfw3dll.a)
endif()