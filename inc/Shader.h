#pragma once

#include <string>
#include <vector>

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Camera.h"
#include "CoreData.h"

class Shader
{
	public:
		// Build shaders.
		Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		~Shader();
		// Activates shaders.
		void Use();
		// Set uniforms.
		void UniformSetBool(const std::string& name, bool value) const;
		void UniformSetInt(const std::string& name, int value) const;
		void UniformSetFloat(const std::string& name, float value) const;
		void UniformSetFloatV(const std::string& name, std::vector<float> value) const;
		void UniformSetMat4(const std::string& name, glm::mat4 value) const;
		// Build matrices
		void UpdateViewMatrix(Camera& camera);
		void UpdateProjectionMatrix(CoreData& c_d, Camera& camera);

		// Shader program.
		unsigned int program;
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;

	private:

};