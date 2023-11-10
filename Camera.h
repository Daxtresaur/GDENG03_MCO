#pragma once
#include "AGameObject.h"
#include "InputListener.h"
#include "InputSystem.h"
#include "Matrix4x4.h"
#include "EngineTime.h"

class Camera : public AGameObject, public InputListener
{
public:
	Camera(std::string name);
	~Camera();

	void update(float deltaTime) override;
	Matrix4x4 getViewMatrix();
	Matrix4x4 getProjectionMatrix();

	void setOrthographicProjectionMatrix(float width, float height, float near_plane, float far_plane);
	void setPerspectiveProjectionMatrix(float field_of_view, float aspect, float near_plane, float far_plane);

	void onKeyUp(int key) override;
	void onKeyDown(int key) override;
	void onMouseMove(const Point deltaPos) override;
	void onLeftMouseDown(const Point deltaPos) override;
	void onLeftMouseUp(const Point deltaPos) override;
	void onRightMouseDown(const Point deltaPos) override;
	void onRightMouseUp(const Point deltaPos) override;

	void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;

	void release() override;

private:
	void updateViewMatrix();

	bool MouseRightClicked = false;

	Matrix4x4 mProjectionMatrix;
};