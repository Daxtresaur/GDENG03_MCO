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

	virtual void onPress(int key) = 0;
	virtual void onRelease(int key) = 0;
	virtual void onMouseMove(const Point delta_position) = 0;
	virtual void onLMBPress(const Point mouse_position) = 0;
	virtual void onLMBRelease(const Point mouse_position) = 0;
	virtual void onRMBPress(const Point mouse_position) = 0;
	virtual void onRMBRelease(const Point mouse_position) = 0;

	virtual void draw(int width, int height, Matrix4x4 view_matrix, Matrix4x4 projection_matrix) = 0;

protected:
	Matrix4x4 mProjectionMatrix;

	bool mIsPerspective = true;
	int mViewportWidth = 1440;
	int mViewportHeight = 900;
	float mFieldOfView = 1.57f;
	float mNearPlane = 0.1f;
	float mFarPlane = 100.f;
};