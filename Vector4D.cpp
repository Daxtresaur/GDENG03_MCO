#include "Vector4D.h"

Vector4D::Vector4D() {
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4D::Vector4D(float v_x, float v_y, float v_z, float v_w) {
	x = v_x;
	y = v_y;
	z = v_z;
	w = v_w;
}

Vector4D::Vector4D(const Vector4D& vector) {
	x = vector.x;
	y = vector.y;
	z = vector.z;
	w = vector.w;
}

void Vector4D::cross(Vector4D& v1, Vector4D& v2, Vector4D& v3) {
	x = (v1.y * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.y * v3.w - v3.y * v2.w) + v1.w * (v2.y * v3.z - v3.y * v2.z));
	y = (v1.x * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.z - v3.x * v2.z)) * -1.f;
	z = (v1.x * (v2.y * v3.w - v3.y * v2.w) - v1.y * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.y - v3.x * v2.y));
	w = (v1.x * (v2.y * v3.z - v3.y * v2.z) - v1.y * (v2.x * v3.z - v3.x * v2.z) + v1.z * (v2.x * v3.y - v3.x * v2.y)) * -1.f;
}