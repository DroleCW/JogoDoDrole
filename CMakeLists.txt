cmake_minimum_required(VERSION 3.16)

project(game)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

include_directories(include)
include_directories(include/graphics/text)

ExternalProject_Add(glfw
	GIT_REPOSITORY https://github.com/glfw/glfw.git 
	PREFIX ./glfw 
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=./glfw
	-DGLFW_BUILD_EXAMPLES=OFF
	-DGLFW_BUILD_TESTS=OFF
	-DGLFW_BUILD_DOCS=OFF
	-DBUILD_SHARED_LIBS=OFF
	UPDATE_COMMAND ""
)

ExternalProject_Add(openal
	GIT_REPOSITORY https://github.com/kcat/openal-soft.git
	PREFIX ./openal
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=./openal
	UPDATE_COMMAND ""
)

ExternalProject_Add(libsndfile
	GIT_REPOSITORY https://github.com/libsndfile/libsndfile.git
	PREFIX ./libsndfile
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=./libsndfile
	-DBUILD_TESTING=OFF
	UPDATE_COMMAND ""
)

ExternalProject_Add(freetype
	GIT_REPOSITORY https://gitlab.freedesktop.org/freetype/freetype.git
	PREFIX ./freetype
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=./freetype
	-DBUILD_SHARED_LIBS=ON
	UPDATE_COMMAND ""
)



add_executable(game ${SOURCES})

set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

if(WIN32)
	target_link_libraries(game ${CMAKE_CURRENT_SOURCE_DIR}/build/glfw/src/glfw-build/src/libglfw3.a)


	add_custom_command(
        TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/build/freetype/src/freetype-build/libfreetype.dll
                ${CMAKE_CURRENT_SOURCE_DIR}/bin/libfreetype.dll)
	target_link_libraries(game ${CMAKE_CURRENT_SOURCE_DIR}/build/freetype/src/freetype-build/libfreetype.dll.a)

	add_custom_command(
        TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/build/openal/src/openal-build/OpenAL32.dll
                ${CMAKE_CURRENT_SOURCE_DIR}/bin/OpenAL32.dll)
	target_link_libraries(game ${CMAKE_CURRENT_SOURCE_DIR}/build/openal/src/openal-build/libOpenAL32.dll.a)


	target_link_libraries(game ${CMAKE_CURRENT_SOURCE_DIR}/build/libsndfile/src/libsndfile-build/libsndfile.a)
	
endif()

if(UNIX)
	find_package(glfw3 3.3 REQUIRED)
	find_package(OpenGL REQUIRED)

	target_include_directories(game PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include> $<INSTALL_INTERFACE:include>)
	target_link_libraries(game PUBLIC glfw OpenGL::GL ${CMAKE_DL_LIBS})
endif()