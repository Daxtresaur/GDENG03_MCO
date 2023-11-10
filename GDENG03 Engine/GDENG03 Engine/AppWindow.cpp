#include"AppWindow.h"
#include"DirectXTex.h"
#include<Windows.h>
#include"imgui.h"
#include"imgui_impl_dx11.h"
#include"imgui_impl_win32.h"
#include"imgui_stdlib.h"
#include"GlobalProperties.h"
#include<iostream>

using namespace std;

#if __cplusplus <= 201402L 
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#endif

AppWindow::AppWindow() {}

AppWindow::~AppWindow() {}

void AppWindow::onCreate() {
	AWindow::onCreate();
	GameObjectManager::initialize();
	AGraphicsEngine::getInstance()->initialize();
	mSwapChain = AGraphicsEngine::getInstance()->createSwapChain();

	RECT windowRect = this->getWindowRect();
	UINT width = windowRect.right - windowRect.left;
	UINT height = windowRect.bottom - windowRect.top;
	mSwapChain->initialize(this->mWindowHandle, width, height);

	SceneCamera* sceneCamera = new SceneCamera("UnregisteredHyperCam2");
	sceneCamera->setPosition(0.f, 0.f, 0.f);
	sceneCamera->setRotation(0.f, 0.f, 0.f);
	sceneCamera->setPerspectiveProjectionMatrix(1.57f, (float)width, (float)height, 0.1f, 100.f);
	SceneCameraManager::getInstance()->setSceneCamera(sceneCamera);

	GameObjectManager::getInstance()->createObject(GameObjectManager::PLANE);
	APlane* object = (APlane*)GameObjectManager::getInstance()->findObjectByName("Plane 0");
	if (object) {
		object->setScale(4.f, 1.f, 4.f);
		object->setPosition(0.f, -1.f, 0.f);
	}

	UIManager::initialize(this->mWindowHandle);

	mGameView.initialize();
}

void AppWindow::onUpdate() {
	AWindow::onUpdate();

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(
		mSwapChain,
		GlobalProperties::BACKGROUND_COLOR[0],
		GlobalProperties::BACKGROUND_COLOR[1],
		GlobalProperties::BACKGROUND_COLOR[2],
		1.f
	);

	RECT windowRect = this->getWindowRect();
	UINT width = windowRect.right - windowRect.left;
	UINT height = windowRect.bottom - windowRect.top;
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(width, height);

	InputManager::getInstance()->update();
	SceneCameraManager::getInstance()->update();

	GameObjectManager::getInstance()->update();
	GameObjectManager::getInstance()->render(width, height);

	UIManager::getInstance()->draw();
	mSwapChain->present(false);

	mGameView.broadcast();
}

void AppWindow::onDestroy() {
	AWindow::onDestroy();
	mGameView.release();
	mSwapChain->release();

	InputManager::destroy();
	SceneCameraManager::destroy();

	GameObjectManager::destroy();
	UIManager::destroy();
	AGraphicsEngine::getInstance()->release();
}