#include "Vector3.h"

#include <cmath>

Vector3::Vector3() {
	x = 0.f;
	y = 0.f;
	z = 0.f;
}

Vector3::Vector3(float vector_x, float vector_y, float vector_z) {
	x = vector_x;
	y = vector_y;
	z = vector_z;
}

Vector3::Vector3(const Vector3& vector) {
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

Vector3 Vector3::lerp(const Vector3& vector_a, const Vector3& vector_b, float coefficient) {
	Vector3 resultVector;

	resultVector.x = vector_a.x * (1.f - coefficient) + vector_b.x * coefficient; 
	resultVector.y = vector_a.y * (1.f - coefficient) + vector_b.y * coefficient;
	resultVector.z = vector_a.z * (1.f - coefficient) + vector_b.z * coefficient;

	return resultVector;
}

void Vector3::operator=(const Vector3& vector) {
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

void Vector3::operator+=(const Vector3& vector) {
	x += vector.x;
	y += vector.y;
	z += vector.z;
}

Vector3 Vector3::operator+(Vector3 vector) {
	return Vector3(x + vector.x, y + vector.y, z + vector.z);
}

Vector3 Vector3::operator-(Vector3 vector)
{
	return Vector3(x - vector.x, y - vector.y, z - vector.z);
}

Vector3 Vector3::operator*(float scalar) {
	return Vector3(scalar * x, scalar * y, scalar * z);
}

void Vector3::Normalize()
{
	float length = sqrt(x * x + y * y + z * z);

	if (length != 0)
	{
		x /= length;
		y /= length;
		z /= length;
	}
}

