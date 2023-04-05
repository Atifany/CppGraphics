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

Quaternion::Quaternion(glm::vec3 eulerAngles)
{
	double cr = cos(eulerAngles.x * 0.5);
	double sr = sin(eulerAngles.x * 0.5);
	double cp = cos(eulerAngles.y * 0.5);
	double sp = sin(eulerAngles.y * 0.5);
	double cy = cos(eulerAngles.z * 0.5);
	double sy = sin(eulerAngles.z * 0.5);

	this->w = cr * cp * cy + sr * sp * sy;
	this->x = sr * cp * cy - cr * sp * sy;
	this->y = cr * sp * cy + sr * cp * sy;
	this->z = cr * cp * sy - sr * sp * cy;
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
	return glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 Quaternion::Upward()
{
	return glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 Quaternion::Leftward()
{
	return glm::vec3(0.0f, 0.0f, 0.0f);
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

void Quaternion::operator*=(const float value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
	this->w *= value;
}
Quaternion Quaternion::operator*(const float value) const
{
	return (Quaternion(
		this->x * value,
		this->y * value,
		this->z * value,
		this->w * value));
}

float Quaternion::norm()
{
	return sqrt(
		this->x * this->x +
		this->y * this->y +
		this->z * this->z +
		this->w * this->w);
}
void Quaternion::normalize()
{
	float n = this->norm();
	if (n == 0)
		return ;
	float toNorm = 1/n;
	
	this->x *= toNorm;
	this->y *= toNorm;
	this->z *= toNorm;
	this->w *= toNorm;
}
void Quaternion::ConvertToUnitNormQuaternion()
{
	float angle = glm::radians(this->w);
	this->w = (float)cos((double)angle / 2);

	glm::vec3 v = glm::vec3(this->x, this->y, this->z);
	glm::normalize(v);
	v *= (float)sin((double)angle / 2);
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

Quaternion Quaternion::conjugate()
{
	float _w = this->w;
	float _x = this->x * -1;
	float _y = this->y * -1;
	float _z = this->z * -1;
	return (Quaternion(_x, _y, _z, _w));
}

Quaternion Quaternion::inverse()
{
	float absVal = this->norm();
	absVal *= absVal;
	absVal = 1/absVal;

	Quaternion conjugateVal = this->conjugate();
	conjugateVal *= absVal;

	return (Quaternion(conjugateVal));
}

glm::vec3 Quaternion::EulerAngles()
{
	this->normalize();
	glm::vec3 ret;

	// roll (z-axis rotation)
	double sinr_cosp = 2 * (this->w * this->x + this->y * this->z);
	double cosr_cosp = 1 - 2 * (this->x * this->x + this->y * this->y);
	ret.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (x-axis rotation)
	double _y = 2 * (this->w * this->y - this->z * this->x);
	if (_y > 1.0)
		_y -= 1.0;
	if (_y < -1.0)
		_y += 1.0;
	ret.y = asin(_y);

	// yaw (y-axis rotation)
	double siny_cosp = 2 * (this->w * this->z + this->x * this->y);
	double cosy_cosp = 1 - 2 * (this->y * this->y + this->z * this->z);
	ret.z = std::atan2(siny_cosp, cosy_cosp);

	return ret;
}
