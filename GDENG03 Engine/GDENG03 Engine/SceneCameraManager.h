#pragma once
#include"SceneCamera.h"

class SceneCameraManager
{
public:
	static SceneCameraManager* getInstance();
	static void destroy();

	void setSceneCamera(SceneCamera* scene_camera);
	void update();

	SceneCamera* getSceneCamera();
	Matrix4x4 getSceneCameraViewMatrix();
	Matrix4x4 getSceneCameraProjectionMatrix();

private:
	SceneCameraManager();
	~SceneCameraManager();
	SceneCameraManager(SceneCameraManager const&) {};
	SceneCameraManager& operator =(SceneCameraManager const&) {};
	static SceneCameraManager* instance;

	SceneCamera* mSceneCamera = nullptr;
};