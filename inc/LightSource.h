#pragma once

#include "glm/glm.hpp"
#include "Component.h"

class LightSource : public Component
{
	public:
		LightSource();
		virtual ~LightSource();

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		float diffuseStrength;
		float specularStrength;

	private:

};

class DirectionalLight : public LightSource
{
	public:
		DirectionalLight();
		~DirectionalLight();
		DirectionalLight(
			glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular,
			float _diffuseStrength, float _specularStrength, glm::vec3 _direction);

		glm::vec3 direction;

	private:
};

class PointLight : public LightSource
{
	public:
		PointLight();
		~PointLight();
		PointLight(
			glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular,
			float _diffuseStrength, float _specularStrength, glm::vec3 _spreadConstants);

		glm::vec3 spreadConstants;

	private:
};
