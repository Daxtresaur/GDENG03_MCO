#pragma once
#include <DirectXMath.h>

using namespace DirectX;

#include "AConstantBuffer.h"
#include "AGameObject.h"
#include "AVertexBuffer.h"
#include "Texture.h"

class AGizmo : public AGameObject
{
public:
	AGizmo(std::string name, void* shader_byte_code, size_t shader_size);
	~AGizmo();

	void update(float delta_time) override;
	void draw(int width, int height, AVertexShader* vertex_shader, APixelShader* pixel_shader, Matrix4x4 view_matrix, Matrix4x4 projection_matrix) override;
	void lookAtCamera(Vector3 cameraPosition);

protected:
	AVertexBuffer* mVertexBuffer;
	AConstantBuffer* mConstantBuffer;
	Texture* texture = nullptr;
	XMFLOAT3 QuaternionToEuler(XMVECTOR quaternion);
};

