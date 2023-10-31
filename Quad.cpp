#include "Quad.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "SceneCameraManager.h"


Quad::Quad(std::string name, void* shaderByteCode, size_t sizeShader) : AGameObject(name)
{
	Vertex Vertex_list[] = {
		// FRONT FACE
		{ Vector3D(-0.5f, 0.f, -0.5f),    Vector3D(1,1,1),  Vector3D(1,1,1) },
		{ Vector3D(-0.5f,  0.f, 0.5f),    Vector3D(1,1,1),  Vector3D(1,1,1) },
		{ Vector3D(0.5f, 0.f,  -0.5f),    Vector3D(1,1,1),  Vector3D(1,1,1) },
		{ Vector3D(0.5f,  0.f,  0.5f),    Vector3D(1,1,1),  Vector3D(1,1,1) },
	};

	m_vb = GraphicsEngine::get()->createVertexBuffer();


	// load the vertices
	m_vb->load(Vertex_list, sizeof(Vertex), ARRAYSIZE(Vertex_list), shaderByteCode, sizeShader);
	CBData ccc;
	ccc.time = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&ccc, sizeof(CBData));
}

Quad::~Quad()
{
}

void Quad::update(float deltaTime)
{
	m_deltaTime = deltaTime;
	m_ticks += m_deltaTime * m_speed;

	Matrix4x4 temp;

	cc.worldMatrix.setScale(localScale);

	temp.setIdentity();
	temp.setRotationZ(localRotation.z * m_speed);
	cc.worldMatrix *= temp;

	temp.setIdentity();
	temp.setRotationY(localRotation.y * m_speed);
	cc.worldMatrix *= temp;

	temp.setIdentity();
	temp.setRotationX(localRotation.x * m_speed);
	cc.worldMatrix *= temp;

	temp.setIdentity();
	temp.setTranslation(localPosition);
	cc.worldMatrix *= temp;
}

void Quad::draw(int width, int height, VertexShader* Vertex_shader, PixelShader* pixel_shader)
{
	cc.viewMatrix.setIdentity();
	cc.viewMatrix = cc.viewMatrix.multiplyTo(SceneCameraManager::getInstance()->getSceneCameraViewMatrix());

	cc.projMatrix.setPerspectiveFovLH(1.57f, ((float)width / height), 0.1f, 100.f);

	cc.time += m_deltaTime;
	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);


	// Set CBData Buffer Data
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(Vertex_shader, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixel_shader, m_cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(Vertex_shader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixel_shader);

	// Set Vertex Data
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// Draw Quad
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Quad::setAnimSpeed(float speed)
{
	m_speed = speed;
}

void Quad::release()
{
}
