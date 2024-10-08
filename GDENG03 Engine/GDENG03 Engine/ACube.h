#pragma once
#include"AGameObject.h"
#include"AInputListener.h"
#include"AVertexBuffer.h"
#include"AIndexBuffer.h"
#include"AConstantBuffer.h"
#include"Matrix4x4.h"

class ACube : public AGameObject, public AInputListener
{
public:
	ACube(std::string name);
	~ACube();

	void update(float delta_time) override;
	void draw(int width, int height, ACamera* camera) override;
	void setTranslationSpeed(float translation_speed);
	void setRotationSpeed(float rotation_speed);
	void setScaleSpeed(float scale_speed);

	void onPress(int key) override;
	void onRelease(int key) override;

	void onMouseMove(Point delta_position) override;
	void onLMBPress(Point mouse_position) override;
	void onLMBRelease(Point mouse_position) override;
	void onRMBPress(Point mouse_position) override;
	void onRMBRelease(Point mouse_position) override;

private:
	AVertexBuffer* mVertexBuffer;
	AIndexBuffer* mIndexBuffer;
	AConstantBuffer* mConstantBuffer;

	AVertexShader* mVertexShader;
	APixelShader* mPixelShader;

	float mTranslationSpeed = 1.f;
	float mRotationSpeed = 1.f;
	float mScaleSpeed = 1.f;

	float mDeltaTime = 0.f;
	float mElapsedTime = 0.f;
};