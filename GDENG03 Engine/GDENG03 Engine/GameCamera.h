#pragma once
#include"ACamera.h"
#include"AVertexBuffer.h"
#include"AIndexBuffer.h"
#include"AConstantBuffer.h"
#include"Texture.h"
#include<DirectXMath.h>

using namespace DirectX;

class GameCamera : public ACamera
{
public:
	GameCamera(std::string name);
	~GameCamera();

	void update(float delta_time) override;
	void draw(int width, int height, ACamera* camera) override;

	void onPress(int key) override;
	void onRelease(int key) override;
	void onMouseMove(const Point delta_position) override;
	void onLMBPress(const Point mouse_position) override;
	void onLMBRelease(const Point mouse_position) override;
	void onRMBPress(const Point mouse_position) override;
	void onRMBRelease(const Point mouse_position) override;

private:
	void faceSceneCamera(Vector3 scene_camera_position);

	AVertexBuffer* mVertexBuffer;
	AConstantBuffer* mConstantBuffer;
	Texture* mTexture = nullptr;

	AVertexShader* mVertexShader;
	APixelShader* mPixelShader;
	Matrix4x4 mIconMatrix;

	float mTranslationSpeed = 1.f;
	float mRotationSpeed = 1.f;
	float mScaleSpeed = 1.f;

	float mDeltaTime = 0.f;
	float mElapsedTime = 0.f;
};