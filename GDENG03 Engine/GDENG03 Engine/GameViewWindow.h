#pragma once
#include"GWindow.h"
#include"AGraphicsEngine.h"
#include"GameObjectManager.h"
#include"InputManager.h"
#include"SceneCameraManager.h"
#include"UIManager.h"
#include"ASwapChain.h"
#include"ADeviceContext.h"
#include"AVertexBuffer.h"
#include"AIndexBuffer.h"
#include"AConstantBuffer.h"
#include"AVertexShader.h"
#include"APixelShader.h"
#include"AGameObject.h"
#include"SceneCamera.h"
#include"Vertex.h"
#include"Matrix4x4.h"
#include"Randomizer.h"

class GameViewWindow : public GWindow
{
public:
	GameViewWindow();
	~GameViewWindow();

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

private:
	ASwapChain* mSwapChain;
	AVertexShader* mVertexShader;
	APixelShader* mPixelShader;
};