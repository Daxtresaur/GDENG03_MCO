#include"ACamera.h"
#include"InputManager.h"
#include<Windows.h>
#include<iostream>

ACamera::ACamera(std::string name) : AGameObject::AGameObject(name) {
	InputManager::getInstance()->addListener(this);
}

ACamera::~ACamera() {
	InputManager::getInstance()->removeListener(this);
}

Matrix4x4 ACamera::getViewMatrix() {
	Matrix4x4 viewMatrix = this->mLocalMatrix;
	viewMatrix.inverse();
	return viewMatrix;
}

void ACamera::setProjection(bool is_perspective) {
	mIsPerspective = is_perspective;
}

void ACamera::setOrthographicProjectionMatrix(float width, float height, float near_plane, float far_plane) {
	mProjectionMatrix.setOrthographicProjection(width, height, near_plane, far_plane);
	setProjection(false);
	setViewportDimensions((int)width, (int)height);
	setClippingPlanes(near_plane, far_plane);
}

void ACamera::setPerspectiveProjectionMatrix(float field_of_view, float width, float height, float near_plane, float far_plane) {
	mProjectionMatrix.setPerspectiveProjection(field_of_view, width / height, near_plane, far_plane);
	setProjection(true);
	setFieldOfView(field_of_view);
	setViewportDimensions((int)width, (int)height);
	setClippingPlanes(near_plane, far_plane);
}

void ACamera::setViewportDimensions(int width, int height) {
	mViewportWidth = width;
	mViewportHeight = height;
}

void ACamera::setClippingPlanes(float near_plane, float far_plane) {
	mNearPlane = near_plane;
	mFarPlane = far_plane;
}

void ACamera::setFieldOfView(float field_of_view) {
	mFieldOfView = field_of_view;
}

Matrix4x4 ACamera::getProjectionMatrix() {
	return mProjectionMatrix;
}

bool ACamera::isPerspective() {
	return mIsPerspective;
}

int ACamera::getViewportWidth() {
	return mViewportWidth;
}

int ACamera::getViewportHeight() {
	return mViewportHeight;
}

float ACamera::getNearPlane() {
	return mNearPlane;
}

float ACamera::getFarPlane() {
	return mFarPlane;
}

float ACamera::getFieldOfView() {
	return mFieldOfView;
}

void ACamera::onPress(int key) {
	switch (key) {
	case 'W':
		std::cout << "W key has been pressed." << std::endl;
		break;
	case 'S':
		std::cout << "S key has been pressed." << std::endl;
		break;
	case 'D':
		std::cout << "D key has been pressed." << std::endl;
		break;
	case 'A':
		std::cout << "A key has been pressed." << std::endl;
		break;
	case 'Q':
		std::cout << "Q key has been pressed." << std::endl;
		break;
	case 'Z':
		std::cout << "Z key has been pressed." << std::endl;
		break;
	}
}

void ACamera::onRelease(int key) {
	switch (key) {
	case 'W':
		std::cout << "W key has been released." << std::endl;
		break;
	case 'S':
		std::cout << "S key has been released." << std::endl;
		break;
	case 'D':
		std::cout << "D key has been released." << std::endl;
		break;
	case 'A':
		std::cout << "A key has been released." << std::endl;
		break;
	case 'Q':
		std::cout << "Q key has been released." << std::endl;
		break;
	case 'Z':
		std::cout << "Z key has been released." << std::endl;
		break;
	}
}

void ACamera::onMouseMove(const Point delta_position) {
	if (InputManager::getInstance()->isKeyDown(VK_RBUTTON)) {
		Vector3 newRotation = this->getLocalRotation();
		newRotation.y += (float)delta_position.getX() * 0.01f;
		newRotation.x += (float)delta_position.getY() * 0.01f;
		this->setRotation(newRotation);
	}
}

void ACamera::onLMBPress(const Point mouse_position) {
	std::cout << "Left mouse button has been pressed." << std::endl;
}

void ACamera::onLMBRelease(const Point mouse_position) {
	std::cout << "Left mouse button has been released." << std::endl;
}

void ACamera::onRMBPress(const Point mouse_position) {
	std::cout << "Right mouse button has been pressed." << std::endl;
}

void ACamera::onRMBRelease(const Point mouse_position) {
	std::cout << "Right mouse button has been released." << std::endl;
}