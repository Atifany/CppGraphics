#pragma once

#include "glm/glm.hpp"

class Material
{
	public:
		Material();
		~Material();
		Material(const Material& other);
		Material operator=(const Material& other);
		Material(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shininess);

		glm::vec3	ambient;
		glm::vec3	diffuse;
		glm::vec3	specular;
		float		shininess;

	private:

};
