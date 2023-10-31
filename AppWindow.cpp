#include "AppWindow.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

#include "Cube.h"
#include "Quad.h"
#include "Vector3D.h"
#include "EngineTime.h"
#include "GraphicsEngine.h"
#include "InputSystem.h"
#include "MathUtils.h"
#include "Matrix4x4.h"
#include "SceneCameraManager.h"
#include"SceneCamera.h"


void AppWindow::onCreate()
{
	GraphicsEngine::get()->init();
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	EngineTime::initialize();
	InputSystem::initialize();
	InputSystem::getInstance()->addListener(this);

	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = getClientWindowRect();
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	std::cout << "hwnd: " << this->m_hwnd;
	m_swap_chain->init(this->m_hwnd, width, height);

	SceneCamera* sceneCamera = new SceneCamera("UnregisteredHyperCam2");
	sceneCamera->setPosition(0.f, 0.f, 0.f);
	sceneCamera->setRotation(0.f, 0.f, 0.f);
	sceneCamera->setPerspectiveProjectionMatrix(1.57f, (float)width / (float)height, 0.1f, 100.f);
	SceneCameraManager::getInstance()->setSceneCamera(sceneCamera);

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	//compile basic vertex shader
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	this->m_vertex_shader = graphEngine->createVertexShader(shaderByteCode, sizeShader);

	for (int i = 0; i < 15; i++) {
		float x = MathUtils::randomFloat(-0.5, 0.5f);
		float y = MathUtils::randomFloat(-0.5, 0.5f);
		float z = MathUtils::randomFloat(-0.5, 0.5f);

		Cube* cubeObject = new Cube("Cube", shaderByteCode, sizeShader);
		cubeObject->setAnimSpeed(MathUtils::randomFloat(-3.75f, 3.75f));
		cubeObject->setPosition(Vector3D(x, y, z));
		cubeObject->setScale(Vector3D(0.25, 0.25, 0.25));
		this->objectList.push_back(cubeObject);
	}

	graphEngine->releaseCompiledShader(); // this must be called after compilation of each shader

	//compile basic pixel shader
	graphEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->m_pixel_shader = graphEngine->createPixelShader(shaderByteCode, sizeShader);
	graphEngine->releaseCompiledShader();


	UIManager::initialize(Window::getHWND());
	GameObjectManager::initialize();


}

void AppWindow::onUpdate()
{
	ticks += EngineTime::getDeltaTime() * 1.0f;

	InputSystem::getInstance()->update();
	SceneCameraManager::getInstance()->update();

	// (Your code process and dispatch Win32 messages)
	// Start the Dear ImGui frame
	//ImGui_ImplDX11_NewFrame();
	//ImGui_ImplWin32_NewFrame();
	//ImGui::NewFrame();

	////ImGui Implementation
	//ImGui::Begin("Scene Settings",nullptr, ImGuiWindowFlags_NoResize);

	//static bool showDemo = false;

	//ImGui::Text("Below our settings for configuring the Scene");
	//ImGui::Checkbox("Show Demo Window", &showDemo);

	//if (showDemo)
	//{
	//	ImGui::ShowDemoWindow(); // Show demo window! :)
	//}

	//static float colour[4] = {0,0,0,1};
	//static ImGuiColorEditFlags colourFlags = ImGuiColorEditFlags_NoAlpha;

	//ImGui::ColorEdit4("Colour", colour, colourFlags);

	//static bool playAnim = true;
	//std::string switchAnim = "Play Animation";

	//if (!playAnim) 
	//{
	//	switchAnim = "Resume Animation";
	//}

	//if (ImGui::Button(switchAnim.c_str()))
	//{
	//	playAnim = !playAnim;
	//}

	//ImGui::End();

	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(m_swap_chain, 0, 0.3f, 0.4f, 1);

	RECT rc = getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(width, height);

	/*for (int i = 0; i < objectList.size(); i++) {
		if (playAnim) 
		{
			objectList[i]->update(EngineTime::getDeltaTime());
		}
		objectList[i]->draw(width, height, m_vertex_shader, m_pixel_shader);
	}*/

	//// END imgui
	//// (Your code clears your framebuffer, renders your other stuff etc.)
	//ImGui::Render();
	//ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	//// (Your code calls swapchain's Present() function)

	GameObjectManager::getInstance()->updateAll();
	GameObjectManager::getInstance()->renderAll(width,height,m_vertex_shader,m_pixel_shader);

	UIManager::getInstance()->drawAllUI();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();/*
	m_vertex_buffer->release();
	m_index_buffer->release();
	m_constant_buffer->release();*/

	m_vertex_shader->release();
	m_pixel_shader->release();

	InputSystem::destroy();
	SceneCameraManager::destroy();
	GraphicsEngine::get()->release();

	/*ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();*/
}

void AppWindow::onKeyDown(int key)
{
	cout << "onkeydown:\n";
	if (InputSystem::getInstance()->isKeyDown('W'))
	{
		cout << "W pressed\n";
	}
}

void AppWindow::onKeyUp(int key)
{
	cout << "onkeyup:\n";
	if (InputSystem::getInstance()->isKeyUp('W'))
	{
		cout << "W released\n";
	}
}

void AppWindow::onMouseMove(const Point deltaPos)
{
	cout << " mouse moved: " << deltaPos.getX() << ", " << deltaPos.getY() << "\n";
}

void AppWindow::onLeftMouseDown(const Point deltaPos)
{
}

void AppWindow::onLeftMouseUp(const Point deltaPos)
{
}

void AppWindow::onRightMouseDown(const Point deltaPos)
{
}

void AppWindow::onRightMouseUp(const Point deltaPos)
{
}

AppWindow::AppWindow()
{

}

AppWindow::~AppWindow()
{

}
