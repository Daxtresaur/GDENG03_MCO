#pragma once

class Vector4D
{
public:
	Vector4D();
	Vector4D(float v_x, float v_y, float v_z, float v_w);
	Vector4D(const Vector4D& vector);
	~Vector4D() {}

	void cross(Vector4D& v1, Vector4D& v2, Vector4D& v3);

	float x;
	float y;
	float z;
	float w;
};