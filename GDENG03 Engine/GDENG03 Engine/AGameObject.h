#pragma once
#include"Vector3.h"
#include"Matrix4x4.h"
#include<string>
#include"AVertexShader.h"
#include"APixelShader.h"

class ACamera;

class AGameObject
{
public:
	AGameObject(std::string name);
	~AGameObject();

	virtual void update(float delta_time) = 0;
	virtual void draw(int width, int height, ACamera* camera) = 0;

	std::string getObjectName();
	bool isActive();
	void setActive(bool is_object_active);
	void select();
	void deselect();

	void setPosition(float x, float y, float z);
	void setPosition(Vector3 position);
	Vector3 getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3 scale);
	Vector3 getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3 rotation);
	Vector3 getLocalRotation();

	void updateLocalMatrix();
	void updateRotationMatrix(const Matrix4x4& rotationMatrix);
	Matrix4x4 getLocalMatrix();

	__declspec(align(16))
		struct constant {
		Matrix4x4 worldMatrix;
		Matrix4x4 viewMatrix;
		Matrix4x4 projectionMatrix;
		float coefficient;
	};

protected:
	std::string mObjectName;
	Vector3 mLocalPosition;
	Vector3 mLocalScale;
	Vector3 mLocalRotation;
	Matrix4x4 mLocalMatrix;

	bool mIsActive = true;
	bool mIsSelected = false;
};