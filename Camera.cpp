#include "Camera.h"

Camera::Camera(std::string name) : AGameObject::AGameObject(name)
{
	InputSystem::getInstance()->addListener(this);
	this->setPosition(0, 0, -5);
	this->updateViewMatrix();
}

Camera::~Camera()
{
	InputSystem::getInstance()->removeListener(this);
}

void Camera::update(float deltaTime)
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

Matrix4x4 Camera::getViewMatrix()
{
	Matrix4x4 viewMatrix = this->localMatrix;
	viewMatrix.inverse();
	return viewMatrix;
}

Matrix4x4 Camera::getProjectionMatrix() {
	return mProjectionMatrix;
}

void Camera::setOrthographicProjectionMatrix(float width, float height, float near_plane, float far_plane) {
	mProjectionMatrix.setOrthoLH(width, height, near_plane, far_plane);
}

void Camera::setPerspectiveProjectionMatrix(float field_of_view, float aspect, float near_plane, float far_plane) {
	mProjectionMatrix.setPerspectiveFovLH(field_of_view, aspect, near_plane, far_plane);
}


void Camera::onKeyUp(int key)
{
	/*switch (key) {
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
	}*/
}

void Camera::onKeyDown(int key)
{
	/*switch (key) {
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
	}*/
}

void Camera::onMouseMove(const Point deltaPos)
{
	if (!MouseRightClicked)
	{
		return;
	}

	Vector3D newRotation = this->getLocalRotation();
	newRotation.y += (float)deltaPos.getX() * 0.01f;
	newRotation.x += (float)deltaPos.getY() * 0.01f;

	this->setRotation(newRotation);

	updateViewMatrix();
}

void Camera::onLeftMouseDown(const Point deltaPos)
{
	std::cout << "Left mouse button pressed" << std::endl;
}

void Camera::onLeftMouseUp(const Point deltaPos)
{
	std::cout << "Left mouse button released" << std::endl;
}

void Camera::onRightMouseDown(const Point deltaPos)
{
	std::cout << "Right mouse button pressed" << std::endl;
	MouseRightClicked = true;
}

void Camera::onRightMouseUp(const Point deltaPos)
{
	std::cout << "Right mouse button released" << std::endl;
	MouseRightClicked = false;
}

void Camera::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
}

void Camera::release()
{
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCamMatrix;
	Vector3D localRotation = this->getLocalRotation();

	worldCamMatrix.setIdentity();
	worldCamMatrix.rotate(0, localRotation.x);
	worldCamMatrix.rotate(1, localRotation.y);
	worldCamMatrix.rotate(2, localRotation.z);
	worldCamMatrix.translate(this->getLocalPosition());
	this->localMatrix = worldCamMatrix;
}