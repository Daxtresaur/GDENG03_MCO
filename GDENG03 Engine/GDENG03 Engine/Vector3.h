#pragma once

class Vector3
{
public:
	Vector3();
	Vector3(float vector_x, float vector_y, float vector_z);
	Vector3(const Vector3& vector);
	~Vector3() {}

	static Vector3 lerp(const Vector3& vector_a, const Vector3& vector_b, float coefficient);

	void operator =(const Vector3& vector);
	void operator +=(const Vector3& vector);
	Vector3 operator +(Vector3 vector);
	Vector3 operator -(Vector3 vector);
	Vector3 operator *(float scalar);

	void Normalize();

	static Vector3 cross(const Vector3& v1, const Vector3& v2) {
		Vector3 result;
		result.x = v1.y * v2.z - v1.z * v2.y;
		result.y = v1.z * v2.x - v1.x * v2.z;
		result.z = v1.x * v2.y - v1.y * v2.x;
		return result;
	}

	float x;
	float y;
	float z;
};