#include "AGizmo.h"

#include "ADeviceContext.h"
#include "AGraphicsEngine.h"
#include "Vector2.h"
#include <iostream>
#include <cmath>

using namespace std;


struct TextureVertex
{
	Vector3 position;
	Vector2 texcoord;
};

AGizmo::AGizmo(std::string name, void* shader_byte_code, size_t shader_size) : AGameObject::AGameObject(name)
{
	//Create texture
	try
	{
		texture = new Texture(L"camera.png");
	}
	catch (...) {}

	Vector3 positionList[] = {
		Vector3(-0.5f, -0.5f, 0.f),
		Vector3(-0.5f, 0.5f, 0.f),
		Vector3(0.5f, -0.5f, -0.f),
		Vector3(0.5f, 0.5f, 0.f)
	};

	Vector2 texcoordList[] = {
		Vector2(0.f, 0.f),
		Vector2(0.0f, 1.f),
		Vector2(1.f, 0.f),
		Vector2(1.f, 1.f)
	};

	TextureVertex vertexList[] = {
		{positionList[0], texcoordList[3]},
		{positionList[1], texcoordList[2]},
		{positionList[2], texcoordList[1]},
		{positionList[3], texcoordList[0]},
	};

	mVertexBuffer = AGraphicsEngine::getInstance()->createVertexBuffer();
	mVertexBuffer->load(vertexList, sizeof(TextureVertex), 4, shader_byte_code, shader_size);

	constant datablock;
	datablock.coefficient = 0.f;

	mConstantBuffer = AGraphicsEngine::getInstance()->createConstantBuffer();
	mConstantBuffer->load(&datablock, sizeof(constant));

}

AGizmo::~AGizmo()
{
	mVertexBuffer->release();
	mConstantBuffer->release();
}

void AGizmo::update(float delta_time)
{
	
}

void AGizmo::draw(int width, int height, ACamera* camera)
{
}

void AGizmo::lookAtCamera(Vector3 cameraPosition)
{
	
	// Calculate the forward direction (from the gizmo to the camera)
	Vector3 forward = cameraPosition - mLocalPosition;
	forward.Normalize();

	// Assuming left-handed coordinate system, "up" is (0, 1, 0)
	Vector3 up(0, 1, 0);

	// Calculate the right vector by taking the cross product of "up" and "forward"
	Vector3 right = Vector3::cross(up, forward);
	right.Normalize();

	// Calculate the new "up" vector by taking the cross product of "forward" and "right"
	up = Vector3::cross(forward, right);
	up.Normalize();

	// Create a rotation matrix based on the calculated right, up, and forward vectors
	Matrix4x4 rotationMatrix;
	rotationMatrix.setRightVector(right);
	rotationMatrix.setUpVector(up);
	rotationMatrix.setForwardVector(forward);

	// Set the gizmo's world matrix to the new rotation matrix
	updateRotationMatrix(rotationMatrix);
	
}