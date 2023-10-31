#pragma once
#include <string>
#include "Vector3D.h"
#include "Matrix4x4.h"

#include "VertexShader.h"
#include "PixelShader.h"

using namespace std;

class AGameObject
{
public:
	AGameObject(string name);
	~AGameObject();

	// Abstract Methods
	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

	virtual void release()=0;

	string getName();

	bool getActive();
	void setActive(bool setter);

	struct Vertex {
		Vector3D position;
		Vector3D color;
		Vector3D color2;
	};

	_declspec(align(16)) //make CBData a size of 16-bytes.
		struct CBData {
		Matrix4x4 worldMatrix;
		Matrix4x4 viewMatrix;
		Matrix4x4 projMatrix;
		float time;
	};

protected:
	bool IsActive = true;
	string name;
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;
};

