#pragma once

#include <iostream>

#include "glm/glm.hpp"

class Quaternion
{
	public:
		Quaternion();
		~Quaternion();
		Quaternion(float r_x, float r_y, float r_z, float r_w);
		Quaternion(glm::vec3 eulerAngles);
		Quaternion(const Quaternion& other);
		Quaternion& operator=(const Quaternion& other);

		void operator+=(const Quaternion& other);
		Quaternion operator+(const Quaternion& other) const;
		void operator-=(const Quaternion& other);
		Quaternion operator-(const Quaternion& other) const;
		void operator*=(const Quaternion& other);
		Quaternion operator*(const Quaternion& other) const;
		void operator*=(const float other);
		Quaternion operator*(const float other) const;

		float norm();
		void normalize();
		void ConvertToUnitNormQuaternion();

		Quaternion conjugate();
		Quaternion inverse();

		float x, y, z, w;

		glm::vec3 EulerAngles();
		
		glm::vec3 Forward();
		glm::vec3 Upward();
		glm::vec3 Leftward();

		// I have no idea why it does not compile as a free function!
		friend std::ostream& operator<<(std::ostream& os, const Quaternion& object)
		{
			os << "{" << object.x << " " << object.y << " " << object.z << " " << object.w << "}";
			return os;
		}


	private:
		Quaternion multiply(const Quaternion& other) const;

};
