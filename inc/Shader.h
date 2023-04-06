#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader
{
	public:
		// Build shaders.
		Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		// Activates shaders.
		void Use();
		// Set uniforms.
		void UniformSetBool(const std::string& name, bool value) const;
		void UniformSetInt(const std::string& name, int value) const;
		void UniformSetFloat(const std::string& name, float value) const;
		void UniformSetFloatV(const std::string& name, std::vector<float> value) const;
		void UniformSetMat4(const std::string& name, glm::mat4 value) const;

		// Shader program.
		unsigned int program;

	private:

};