cmake_minimum_required(VERSION 3.0.0)
project(cpp_graphics VERSION 0.1.0)

add_executable(cpp_graphics
	sources/main.cpp
	sources/glad.c
	sources/glad.h
	sources/vertexShader.h
	sources/fragmentShader.h
)

target_link_libraries(cpp_graphics glfw ${CMAKE_DL_LIBS})