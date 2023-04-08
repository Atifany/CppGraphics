#include "../inc/Quaternion.h"

Quaternion::Quaternion()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 1.0f;
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
	float yaw = eulerAngles.x;
	float pitch = eulerAngles.y;
	float roll = eulerAngles.z;
	this->x = sin(roll/2) * cos(pitch/2) * cos(yaw/2) - cos(roll/2) * sin(pitch/2) * sin(yaw/2);
	this->y = cos(roll/2) * sin(pitch/2) * cos(yaw/2) + sin(roll/2) * cos(pitch/2) * sin(yaw/2);
	this->z = cos(roll/2) * cos(pitch/2) * sin(yaw/2) - sin(roll/2) * sin(pitch/2) * cos(yaw/2);
	this->w = cos(roll/2) * cos(pitch/2) * cos(yaw/2) + sin(roll/2) * sin(pitch/2) * sin(yaw/2);
	this->normalize();
}

Quaternion::Quaternion(const Quaternion& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	this->w = other.w;
}

Quaternion& Quaternion::operator=(const Quaternion& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	this->w = other.w;
	return *this;
}

glm::vec3 Quaternion::Forward()
{
	glm::vec3 ae = this->EulerAngles();
	glm::vec3 dirVector;

	dirVector.x = cos(ae.x) * cos(ae.y);
	dirVector.y = sin(ae.y);
	dirVector.z = sin(ae.x) * cos(ae.y);
	return glm::normalize(dirVector);
}

glm::vec3 Quaternion::Upward()
{
	glm::vec3 ae = this->EulerAngles();
	glm::vec3 dirVector;

	dirVector.x = cos(M_PI/2 - ae.x) * cos(M_PI/2 - ae.y);
	dirVector.y = sin(M_PI/2 - ae.y);
	dirVector.z = sin(M_PI/2 - ae.x) * cos(M_PI/2 - ae.y);
	return glm::normalize(dirVector);
}

glm::vec3 Quaternion::Leftward()
{
	return glm::normalize(glm::cross(this->Upward(), this->Forward()));
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
	glm::vec3 ret;

	float t0 = 2.0f * (w * x + y * z);
	float t1 = 1.0f - 2.0f * (x * x + y * y);
	ret.z = atan2(t0, t1);

	float t2 = 2.0f * (w * y - z * x);
	if (t2 > 1.0f)
		t2 = 1.0f;
	if (t2 < -1.0f)
		t2 = -1.0f;
	ret.y = asin(t2);

	float t3 = 2.0f * (w * z + x * y);
	float t4 = 1.0f - 2.0f * (y * y + z * z);
	ret.x = atan2(t3, t4);

	return ret;
}

glm::vec4 Quaternion::AxisRotation()
{
	float angle = 2 * acos(this->w);
	glm::vec4 angleAxis;
	angleAxis.x = this->x;
	angleAxis.y = this->y;
	angleAxis.z = this->z;
	angleAxis.w = angle;
	return angleAxis;
}
