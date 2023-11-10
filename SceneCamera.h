#pragma once
#include"Camera.h"

class SceneCamera : public Camera
{
public:
	SceneCamera(std::string name);
	~SceneCamera();

	void update(float deltaTime) override;
};