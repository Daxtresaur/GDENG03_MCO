#pragma once
#include"AGameObject.h"
#include"AInputListener.h"
#include"Matrix4x4.h"

class ACamera : public AGameObject, public AInputListener
{
public:
	ACamera(std::string name);
	~ACamera();

	virtual void update(float delta_time) = 0;
	Matrix4x4 getViewMatrix();

	void setProjection(bool is_perspective);
	void setOrthographicProjectionMatrix(float width, float height, float near_plane, float far_plane);
	void setPerspectiveProjectionMatrix(float field_of_view, float width, float height, float near_plane, float far_plane);
	void setViewportDimensions(int width, int height);
	void setClippingPlanes(float near_plane, float far_plane);
	void setFieldOfView(float field_of_view);

	Matrix4x4 getProjectionMatrix();
	bool isPerspective();
	int getViewportWidth();
	int getViewportHeight();
	float getNearPlane();
	float getFarPlane();
	float getFieldOfView();

	void onPress(int key) override;
	void onRelease(int key) override;
	void onMouseMove(const Point delta_position) override;
	void onLMBPress(const Point mouse_position) override;
	void onLMBRelease(const Point mouse_position) override;
	void onRMBPress(const Point mouse_position) override;
	void onRMBRelease(const Point mouse_position) override;

	virtual void draw(int width, int height, AVertexShader* vertex_shader, APixelShader* pixel_shader) = 0;

protected:
	Matrix4x4 mProjectionMatrix;

	bool mIsPerspective = true;
	int mViewportWidth = 1440;
	int mViewportHeight = 900;
	float mFieldOfView = 1.57f;
	float mNearPlane = 0.1f;
	float mFarPlane = 100.f;
};