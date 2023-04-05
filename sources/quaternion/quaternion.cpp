#include "quaternion.h"

Quaternion::Quaternion()
{
	this->x = 0.0f;
	this->y = 1.0f;
	this->z = 0.0f;
}

Quaternion::~Quaternion() {}

Quaternion::Quaternion(float r_x, float r_y, float r_z, float r_w)
{
	this->x = r_x;
	this->y = r_y;
	this->z = r_z;
	this->w = r_w;
}

Quaternion::Quaternion(const Quaternion& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

Quaternion& Quaternion::operator=(const Quaternion& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	return *this;
}

glm::vec3 Quaternion::Forward()
{
	//return glm::vec3(this->x, this->y, this->z);
}

glm::vec3 Quaternion::Upward()
{

}

glm::vec3 Quaternion::Leftward()
{

}

void Quaternion::operator+=(const Quaternion& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	this->w += other.w;
}
Quaternion Quaternion::operator+(const Quaternion& other) const
{
	float x = this->x + other.x;
	float y = this->y + other.y;
	float z = this->z + other.z;
	float w = this->w + other.w;

	return Quaternion(x, y, z, w);
}

void Quaternion::operator-=(const Quaternion& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	this->w -= other.w;
}
Quaternion Quaternion::operator-(const Quaternion& other) const
{
	float x = this->x - other.x;
	float y = this->y - other.y;
	float z = this->z - other.z;
	float w = this->w - other.w;

	return Quaternion(x, y, z, w);
}

void Quaternion::operator*=(const Quaternion& other)
{
	(*this) = this->multiply(other);
}
Quaternion Quaternion::operator*(const Quaternion& other) const
{
	return this->multiply(other);
}

Quaternion Quaternion::multiply(const Quaternion& other) const
{
	glm::vec3 _axis = glm::vec3(this->x, this->y, this->z);
	glm::vec3 axis = glm::vec3(other.x, other.y, other.z);

	float scalar = this->w * other.w - glm::dot(_axis, axis);

	glm::vec3 imaginary = axis * this->w + _axis * other.w + glm::cross(_axis, axis);

	return Quaternion(imaginary.x, imaginary.y, imaginary.z, scalar);
}

