cmake_minimum_required(VERSION 3.0.0)
project(ft_minecraft VERSION 0.1.0)

add_executable(ft_minecraft
	sources/Quaternion.cpp
	sources/Transform.cpp
	sources/main.cpp
	sources/process_input.cpp
	sources/CoreData.cpp
	sources/Shader.cpp
	sources/Camera.cpp
	sources/Input.cpp
	sources/Renderer.cpp
	sources/Texture.cpp
	sources/Material.cpp
	sources/GameObject.cpp
	sources/Component.cpp
	sources/LightSource.cpp
	sources/Text.cpp

	scripts/sources/CubeScript.cpp
	scripts/sources/PlayerMovement.cpp
	
	#	GLAD library
	inc/glad/glad.c

	#	stb_image library
	inc/stb_image/stb_image_implementation.cpp
	# TEXTWTF/main.cpp
	# inc/glad/glad.c
)

target_include_directories(ft_minecraft PRIVATE "/usr/include/freetype2/")
	
target_link_libraries(ft_minecraft glfw freetype ${CMAKE_DL_LIBS} )