cmake_minimum_required(VERSION 3.0.0)
project(cpp_graphics VERSION 0.1.0)

add_executable(cpp_graphics
	sources/main.cpp
	sources/process_input.cpp
	sources/core_data.cpp
	sources/shader.cpp
	sources/transform.cpp
	sources/camera.cpp
	sources/input.cpp

#	GLAD library
	sources/glad/glad.c

#	stb_image library
	sources/stb_image/stb_image_implementation.cpp
)

target_link_libraries(cpp_graphics glfw ${CMAKE_DL_LIBS})