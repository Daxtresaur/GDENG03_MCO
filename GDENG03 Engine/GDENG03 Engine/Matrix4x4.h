#pragma once
#include<memory>
#include"Vector3.h"
#include"Vector4.h"

class Matrix4x4
{
public:
	Matrix4x4();
	~Matrix4x4();

	void setIdentity();
	void setTranslation(float delta_x, float delta_y, float delta_z);
	void setTranslation(const Vector3& translate_vector);
	void setScale(float factor_x, float factor_y, float factor_z);
	void setScale(const Vector3& scale_vector);
	void setRotationX(float theta);
	void setRotationY(float theta);
	void setRotationZ(float theta);
	
	void setOrthographicProjection(float width, float height, float near_plane, float far_plane);
	void setPerspectiveProjection(float field_of_view, float aspect, float near_plane, float far_plane);

	void translate(float delta_x, float delta_y, float delta_z);
	void translate(const Vector3& translate_vector);
	void scale(float factor_x, float factor_y, float factor_z);
	void scale(const Vector3& scale_vector);
	void rotate(int axis, float theta);

	void operator *=(const Matrix4x4& matrix);
	void setMatrix(const Matrix4x4& matrix);

	Vector3 getRightVector();
	Vector3 getUpVector();
	Vector3 getForwardVector();
	Vector3 getTranslation();
	float getDeterminant();
	void inverse();

	void setRightVector(Vector3 right);
	void setUpVector(Vector3 up);
	void setForwardVector(Vector3 forward);
	bool isEqualTo(const Matrix4x4& other_matrix);

	float mMatrix[4][4] = {};
};