#pragma once
#include"ACamera.h"

class SceneCamera : public ACamera
{
public:
	SceneCamera(std::string name);
	~SceneCamera();

	void update(float delta_time) override;
	void draw(int width, int height, AVertexShader* vertex_shader, APixelShader* pixel_shader, bool is_scene_view) override;

	void onPress(int key) override;
	void onRelease(int key) override;
	void onMouseMove(const Point delta_position) override;
	void onLMBPress(const Point mouse_position) override;
	void onLMBRelease(const Point mouse_position) override;
	void onRMBPress(const Point mouse_position) override;
	void onRMBRelease(const Point mouse_position) override;
};