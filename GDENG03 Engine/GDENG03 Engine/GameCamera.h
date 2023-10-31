#pragma once
#include"ACamera.h"
#include"AVertexBuffer.h"
#include"AIndexBuffer.h"
#include"AConstantBuffer.h"

class GameCamera : public ACamera
{
public:
	GameCamera(std::string name, void* shader_byte_code, size_t shader_size);
	~GameCamera();

	void update(float delta_time) override;
	void draw(int width, int height, AVertexShader* vertex_shader, APixelShader* pixel_shader) override;

private:
	AVertexBuffer* mVertexBuffer;
	AIndexBuffer* mIndexBuffer;
	AConstantBuffer* mConstantBuffer;

	float mTranslationSpeed = 1.f;
	float mRotationSpeed = 1.f;
	float mScaleSpeed = 1.f;

	float mDeltaTime = 0.f;
	float mElapsedTime = 0.f;
};