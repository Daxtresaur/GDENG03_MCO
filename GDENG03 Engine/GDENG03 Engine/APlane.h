#pragma once
#include"AGameObject.h"
#include"AVertexBuffer.h"
#include"AConstantBuffer.h"

class APlane : public AGameObject
{
public:
	APlane(std::string name);
	~APlane();

	void update(float delta_time) override;
	void draw(int width, int height, Matrix4x4 view_matrix, Matrix4x4 projection_matrix) override;
	void setTranslationSpeed(float translation_speed);
	void setRotationSpeed(float rotation_speed);
	void setScaleSpeed(float scale_speed);

private:
	AVertexBuffer* mVertexBuffer;
	AConstantBuffer* mConstantBuffer;

	AVertexShader* mVertexShader;
	APixelShader* mPixelShader;

	float mTranslationSpeed = 1.f;
	float mRotationSpeed = 1.f;
	float mScaleSpeed = 1.f;
};