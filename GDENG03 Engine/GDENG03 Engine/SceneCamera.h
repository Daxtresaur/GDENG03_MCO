#pragma once
#include"ACamera.h"

class SceneCamera : public ACamera
{
public:
	SceneCamera(std::string name);
	~SceneCamera();

	void update(float delta_time) override;
	void draw(int width, int height, AVertexShader* vertex_shader, APixelShader* pixel_shader) override;
};