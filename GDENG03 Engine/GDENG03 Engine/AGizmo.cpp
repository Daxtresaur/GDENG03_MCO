#include "AGizmo.h"

#include "ADeviceContext.h"
#include "AGraphicsEngine.h"
#include "Vector2.h"
#include "iostream"

using namespace std;


struct TextureVertex
{
	Vector3 position;
	Vector2 texcoord;
};

AGizmo::AGizmo(std::string name, void* shader_byte_code, size_t shader_size) : AGameObject::AGameObject(name)
{
	//CreateTexture
	try
	{
		texture = new Texture(L".\\wood.dds");
	}
	catch (...) {}

	Vector3 positionList[] = {
		Vector3(-0.5f, 0.5f, 0.f),
		Vector3(0.5f, 0.5f, 0.f),
		Vector3(-0.5f, -0.5f, -0.f),
		Vector3(0.5f, -0.5f, 0.f)
	};

	Vector2 texcoordList[] = {
		Vector2(0.f, 0.f),
		Vector2(0.0f, 1.f),
		Vector2(1.f, 0.f),
		Vector2(1.f, 1.f)
	};

	TextureVertex vertexList[] = {
		{positionList[0], texcoordList[0]},
		{positionList[1], texcoordList[1]},
		{positionList[2], texcoordList[2]},
		{positionList[3], texcoordList[3]},
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

void AGizmo::draw(int width, int height, AVertexShader* vertex_shader, APixelShader* pixel_shader,
	Matrix4x4 view_matrix, Matrix4x4 projection_matrix)
{
	constant shaderNumbers;

	shaderNumbers.worldMatrix = this->getLocalMatrix();
	shaderNumbers.viewMatrix = view_matrix;
	shaderNumbers.projectionMatrix = projection_matrix;
	shaderNumbers.coefficient = 0.f;

	mConstantBuffer->update(AGraphicsEngine::getInstance()->getImmediateDeviceContext(), &shaderNumbers);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(mConstantBuffer, vertex_shader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(mConstantBuffer, pixel_shader);
	

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(vertex_shader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(pixel_shader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(mVertexBuffer);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setTexture(texture, pixel_shader);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(mVertexBuffer->getVertexCount(), 0);
}

