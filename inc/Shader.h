#pragma once

#include <string>
#include <vector>

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Camera.h"
#include "CoreData.h"
#include "LightSource.h"
#include "GameObject.h"

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
		void UniformSetVec2(const std::string& name, glm::vec2 value) const;
		void UniformSetVec3(const std::string& name, glm::vec3 value) const;
		void UniformSetVec4(const std::string& name, glm::vec4 value) const;
		void UniformSetMat4(const std::string& name, glm::mat4 value) const;
		// Build matrices
		void UpdateViewMatrix(GameObject* camera);
		void UpdateProjectionMatrix(CoreData& c_d, GameObject* camera);
		void UpdateLightUniforms();

		// Shader program.
		unsigned int program;
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;

	private:

};