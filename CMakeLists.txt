cmake_minimum_required(VERSION 3.0.0)
project(cpp_graphics VERSION 0.1.0)

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

	scripts/sources/CubeScript.cpp
	scripts/sources/PlayerMovement.cpp

#	GLAD library
	inc/glad/glad.c

#	stb_image library
	inc/stb_image/stb_image_implementation.cpp
)

target_link_libraries(ft_minecraft glfw ${CMAKE_DL_LIBS})