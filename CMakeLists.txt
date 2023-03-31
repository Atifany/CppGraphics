cmake_minimum_required(VERSION 3.0.0)
project(cpp_graphics VERSION 0.1.0)

add_executable(cpp_graphics
	sources/main.cpp
	sources/glad.c
	sources/glad.h
	sources/process_input.cpp
	sources/core_data.h
	sources/core_data.cpp
	sources/shader.h
	sources/shader.cpp
)

target_link_libraries(cpp_graphics glfw ${CMAKE_DL_LIBS})