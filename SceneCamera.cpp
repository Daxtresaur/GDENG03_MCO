#include "SceneCamera.h"

SceneCamera::SceneCamera(std::string name) : Camera::Camera(name) {}

SceneCamera::~SceneCamera() {}

void SceneCamera::update(float deltaTime)
{
	Vector3D newPosition = this->getLocalPosition();
	float movementSpeed = 5.f;
	float movementScalar;

	if (InputSystem::getInstance()->isKeyDown('W'))
	{
		movementScalar = deltaTime * movementSpeed * 1.f;
		newPosition += this->localMatrix.getZDirection() * movementScalar;
		this->setPosition(newPosition);

		updateViewMatrix();
	}

	else if (InputSystem::getInstance()->isKeyDown('S'))
	{
		movementScalar = deltaTime * movementSpeed * -1.f;
		newPosition += this->localMatrix.getZDirection() * movementScalar;
		this->setPosition(newPosition);

		updateViewMatrix();
	}

	else if (InputSystem::getInstance()->isKeyDown('D'))
	{
		movementScalar = deltaTime * movementSpeed * 1.f;
		newPosition += this->localMatrix.getXDirection() * movementScalar;
		this->setPosition(newPosition);

		updateViewMatrix();
	}

	else if (InputSystem::getInstance()->isKeyDown('A'))
	{
		movementScalar = deltaTime * movementSpeed * -1.f;
		newPosition += this->localMatrix.getXDirection() * movementScalar;
		this->setPosition(newPosition);

		updateViewMatrix();
	}

	else if (InputSystem::getInstance()->isKeyDown('Q'))
	{
		movementScalar = deltaTime * movementSpeed * 1.f;
		newPosition += this->localMatrix.getYDirection() * movementScalar;
		this->setPosition(newPosition);

		updateViewMatrix();
	}

	else if (InputSystem::getInstance()->isKeyDown('Z'))
	{
		movementScalar = deltaTime * movementSpeed * -1.f;
		newPosition += this->localMatrix.getYDirection() * movementScalar;
		this->setPosition(newPosition);

		updateViewMatrix();
	}
}