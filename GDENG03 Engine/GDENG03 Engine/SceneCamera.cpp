#include"SceneCamera.h"
#include"InputManager.h"
#include<Windows.h>

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