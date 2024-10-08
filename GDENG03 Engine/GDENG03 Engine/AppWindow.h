#pragma once
#include"AWindow.h"
#include"GameViewWindow.h"
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
#include"ACube.h"
#include"APlane.h"
#include"ACamera.h"
#include"SceneCamera.h"
#include"Vertex.h"
#include"Matrix4x4.h"
#include"Randomizer.h"
#include<vector>

class AppWindow : public AWindow
{
public:
	AppWindow();
	~AppWindow();

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

private:
	GameViewWindow mGameView;

	ASwapChain* mSwapChain;
	AVertexBuffer* mVertexBuffer;
	AIndexBuffer* mIndexBuffer;
	AConstantBuffer* mConstantBuffer;
};