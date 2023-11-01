#include"SceneCamera.h"
#include"InputManager.h"
#include<Windows.h>
#include<iostream>

SceneCamera::SceneCamera(std::string name) : ACamera::ACamera(name) {}

SceneCamera::~SceneCamera() {}

void SceneCamera::update(float delta_time) {
	if (InputManager::getInstance()->isKeyDown(VK_RBUTTON)) {
		Vector3 newPosition = this->getLocalPosition();
		float movementSpeed = 5.f;
		float movementScalar;

		if (InputManager::getInstance()->isKeyDown('W')) {
			movementScalar = delta_time * movementSpeed * 1.f;
			newPosition += (this->mLocalMatrix.getForwardVector() * movementScalar);
			this->setPosition(newPosition);
		}

		else if (InputManager::getInstance()->isKeyDown('S')) {
			movementScalar = delta_time * movementSpeed * -1.f;
			newPosition += (this->mLocalMatrix.getForwardVector() * movementScalar);
			this->setPosition(newPosition);
		}

		else if (InputManager::getInstance()->isKeyDown('D')) {
			movementScalar = delta_time * movementSpeed * 1.f;
			newPosition += (this->mLocalMatrix.getRightVector() * movementScalar);
			this->setPosition(newPosition);
		}

		else if (InputManager::getInstance()->isKeyDown('A')) {
			movementScalar = delta_time * movementSpeed * -1.f;
			newPosition += (this->mLocalMatrix.getRightVector() * movementScalar);
			this->setPosition(newPosition);
		}

		else if (InputManager::getInstance()->isKeyDown('Q')) {
			movementScalar = delta_time * movementSpeed * 1.f;
			newPosition += (this->mLocalMatrix.getUpVector() * movementScalar);
			this->setPosition(newPosition);
		}

		else if (InputManager::getInstance()->isKeyDown('Z')) {
			movementScalar = delta_time * movementSpeed * -1.f;
			newPosition += (this->mLocalMatrix.getUpVector() * movementScalar);
			this->setPosition(newPosition);
		}
	}
}

void SceneCamera::draw(int width, int height, AVertexShader* vertex_shader, APixelShader* pixel_shader, bool is_scene_view) {}

void SceneCamera::onPress(int key) {
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

void SceneCamera::onRelease(int key) {
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

void SceneCamera::onMouseMove(const Point delta_position) {
	if (InputManager::getInstance()->isKeyDown(VK_RBUTTON)) {
		Vector3 newRotation = this->getLocalRotation();
		newRotation.y += (float)delta_position.getX() * 0.01f;
		newRotation.x += (float)delta_position.getY() * 0.01f;
		this->setRotation(newRotation);
	}
}

void SceneCamera::onLMBPress(const Point mouse_position) {
	std::cout << "Left mouse button has been pressed." << std::endl;
}

void SceneCamera::onLMBRelease(const Point mouse_position) {
	std::cout << "Left mouse button has been released." << std::endl;
}

void SceneCamera::onRMBPress(const Point mouse_position) {
	std::cout << "Right mouse button has been pressed." << std::endl;
}

void SceneCamera::onRMBRelease(const Point mouse_position) {
	std::cout << "Right mouse button has been released." << std::endl;
}