#include"GameViewWindow.h"
#include"GlobalProperties.h"

GameViewWindow::GameViewWindow() {
}

GameViewWindow::~GameViewWindow() {
}

void GameViewWindow::onCreate() {
	GWindow::onCreate();
	mSwapChain = AGraphicsEngine::getInstance()->createSwapChain();

	RECT windowRect = this->getWindowRect();
	UINT width = windowRect.right - windowRect.left;
	UINT height = windowRect.bottom - windowRect.top;
	mSwapChain->initialize(this->mWindowHandle, width, height);

	void* shaderByteCode = nullptr;
	size_t shaderSize;

	AGraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &shaderSize);
	mVertexShader = AGraphicsEngine::getInstance()->createVertexShader(shaderByteCode, shaderSize);
	AGraphicsEngine::getInstance()->releaseCompiledVertexShader();

	AGraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &shaderSize);
	mPixelShader = AGraphicsEngine::getInstance()->createPixelShader(shaderByteCode, shaderSize);
	AGraphicsEngine::getInstance()->releaseCompiledPixelShader();
}

void GameViewWindow::onUpdate() {
	GWindow::onUpdate();
	GameCamera* gameCam = GameObjectManager::getInstance()->getSelectedCamera();

	if (gameCam) {
		AGraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(
			mSwapChain,
			GlobalProperties::BACKGROUND_COLOR[0],
			GlobalProperties::BACKGROUND_COLOR[1],
			GlobalProperties::BACKGROUND_COLOR[2],
			1.f
		);
	}

	else {
		AGraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(
			mSwapChain,
			0.f,
			0.f,
			0.f,
			1.f
		);
	}

	RECT windowRect = this->getWindowRect();
	UINT width = windowRect.right - windowRect.left;
	UINT height = windowRect.bottom - windowRect.top;
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(width, height);

	if (gameCam) GameObjectManager::getInstance()->renderToGameCamera(width, height, mVertexShader, mPixelShader, gameCam);
	mSwapChain->present(false);
}

void GameViewWindow::onDestroy() {
	GWindow::onDestroy();
	mSwapChain->release();
	mVertexShader->release();
	mPixelShader->release();
}