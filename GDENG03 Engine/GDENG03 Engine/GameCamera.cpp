#include"GameCamera.h"
#include"AGraphicsEngine.h"
#include"InputManager.h"
#include"SceneCameraManager.h"
#include"ADeviceContext.h"
#include<iostream>
#include"GlobalProperties.h"
#include"Vector2.h"
#include<cmath>

struct TextureVertex
{
	Vector3 position;
	Vector2 texcoord;
};

GameCamera::GameCamera(std::string name) : ACamera::ACamera(name) {
	//Create texture
	try {
		mTexture = new Texture(L"camera.png");
	}
	catch (...) {}

	void* shaderByteCode = nullptr;
	size_t shaderSize;
	AGraphicsEngine::getInstance()->compileVertexShader(L"TextureVertexShader.hlsl", "vsmain", &shaderByteCode, &shaderSize);

	Vector3 positionList[] = {
		Vector3(-0.5f, -0.5f, 0.f),
		Vector3(-0.5f, 0.5f, 0.f),
		Vector3(0.5f, -0.5f, -0.f),
		Vector3(0.5f, 0.5f, 0.f)
	};

	Vector2 texcoordList[] = {
		Vector2(0.f, 0.f),
		Vector2(0.0f, 1.f),
		Vector2(1.f, 0.f),
		Vector2(1.f, 1.f)
	};

	TextureVertex vertexList[] = {
		{positionList[0], texcoordList[3]},
		{positionList[1], texcoordList[2]},
		{positionList[2], texcoordList[1]},
		{positionList[3], texcoordList[0]},
	};

	mVertexBuffer = AGraphicsEngine::getInstance()->createVertexBuffer();
	mVertexBuffer->load(vertexList, sizeof(TextureVertex), 4, shaderByteCode, shaderSize);

	constant datablock;
	datablock.coefficient = 0.f;

	mConstantBuffer = AGraphicsEngine::getInstance()->createConstantBuffer();
	mConstantBuffer->load(&datablock, sizeof(constant));

	mVertexShader = AGraphicsEngine::getInstance()->createVertexShader(shaderByteCode, shaderSize);
	AGraphicsEngine::getInstance()->releaseCompiledVertexShader();

	AGraphicsEngine::getInstance()->compilePixelShader(L"TexturePixelShader.hlsl", "psmain", &shaderByteCode, &shaderSize);
	mPixelShader = AGraphicsEngine::getInstance()->createPixelShader(shaderByteCode, shaderSize);
	AGraphicsEngine::getInstance()->releaseCompiledPixelShader();

	InputManager::getInstance()->addListener(this);

	mViewportWidth = GlobalProperties::GAME_VIEW_WIDTH;
	mViewportHeight = GlobalProperties::GAME_VIEW_HEIGHT;

	mIconMatrix.setIdentity();
}

GameCamera::~GameCamera() {
	mVertexBuffer->release();
	mConstantBuffer->release();

	mVertexShader->release();
	mPixelShader->release();
	delete mTexture;

	InputManager::getInstance()->removeListener(this);
}

void GameCamera::update(float delta_time) {
	if (this->mIsSelected) {
		if (InputManager::getInstance()->isKeyDown('R')) {
			if (InputManager::getInstance()->isKeyDown(VK_UP)) {
				float deltaRotation = mRotationSpeed * delta_time;
				Vector3 newRotation = this->getLocalRotation();
				newRotation += Vector3(deltaRotation, deltaRotation, deltaRotation);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown(VK_DOWN)) {
				float deltaRotation = -mRotationSpeed * delta_time;
				Vector3 newRotation = this->getLocalRotation();
				newRotation += Vector3(deltaRotation, deltaRotation, deltaRotation);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('I')) {
				Vector3 newRotation = this->getLocalRotation();
				newRotation += Vector3(mRotationSpeed * delta_time, 0.f, 0.f);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('K')) {
				Vector3 newRotation = this->getLocalRotation();
				newRotation += Vector3(-mRotationSpeed * delta_time, 0.f, 0.f);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('L')) {
				Vector3 newRotation = this->getLocalRotation();
				newRotation += Vector3(0.f, -mRotationSpeed * delta_time, 0.f);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('J')) {
				Vector3 newRotation = this->getLocalRotation();
				newRotation += Vector3(0.f, mRotationSpeed * delta_time, 0.f);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('O')) {
				Vector3 newRotation = this->getLocalRotation();
				newRotation += Vector3(0.f, 0.f, -mRotationSpeed * delta_time);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('U')) {
				Vector3 newRotation = this->getLocalRotation();
				newRotation += Vector3(0.f, 0.f, mRotationSpeed * delta_time);
				this->setRotation(newRotation);
			}
		}

		else if (InputManager::getInstance()->isKeyDown('T')) {
			float translationScalar = mTranslationSpeed * delta_time;

			if (InputManager::getInstance()->isKeyDown('I')) {
				Vector3 newPosition = this->getLocalPosition();
				newPosition += this->mLocalMatrix.getUpVector() * translationScalar;
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('K')) {
				Vector3 newPosition = this->getLocalPosition();
				newPosition += this->mLocalMatrix.getUpVector() * -translationScalar;
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('L')) {
				Vector3 newPosition = this->getLocalPosition();
				newPosition += this->mLocalMatrix.getRightVector() * translationScalar;
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('J')) {
				Vector3 newPosition = this->getLocalPosition();
				newPosition += this->mLocalMatrix.getRightVector() * -translationScalar;
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('U')) {
				Vector3 newPosition = this->getLocalPosition();
				newPosition += this->mLocalMatrix.getForwardVector() * translationScalar;
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('M')) {
				Vector3 newPosition = this->getLocalPosition();
				newPosition += this->mLocalMatrix.getForwardVector() * -translationScalar;
				this->setPosition(newPosition);
			}
		}

		else if (InputManager::getInstance()->isKeyDown('Y')) {
			if (InputManager::getInstance()->isKeyDown(VK_UP)) {
				float deltaScale = mScaleSpeed * delta_time;
				Vector3 newScale = this->getLocalScale();
				newScale += Vector3(deltaScale, deltaScale, deltaScale);
				this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown(VK_DOWN)) {
				float deltaScale = -mScaleSpeed * delta_time;
				Vector3 newScale = this->getLocalScale();
				newScale += Vector3(deltaScale, deltaScale, deltaScale);
				if (newScale.x > 0.f && newScale.y > 0.f && newScale.z > 0.f) this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('I')) {
				Vector3 newScale = this->getLocalScale();
				newScale += Vector3(0.f, mScaleSpeed * delta_time, 0.f);
				this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('K')) {
				Vector3 newScale = this->getLocalScale();
				newScale += Vector3(0.f, -mScaleSpeed * delta_time, 0.f);
				if (newScale.y > 0.f) this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('L')) {
				Vector3 newScale = this->getLocalScale();
				newScale += Vector3(mScaleSpeed * delta_time, 0.f, 0.f);
				this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('J')) {
				Vector3 newScale = this->getLocalScale();
				newScale += Vector3(-mScaleSpeed * delta_time, 0.f, 0.f);
				if (newScale.x > 0.f) this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('U')) {
				Vector3 newScale = this->getLocalScale();
				newScale += Vector3(0.f, 0.f, mScaleSpeed * delta_time);
				this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('M')) {
				Vector3 newScale = this->getLocalScale();
				newScale += Vector3(0.f, 0.f, -mScaleSpeed * delta_time);
				if (newScale.z > 0.f) this->setScale(newScale);
			}
		}
	}
}

void GameCamera::draw(int width, int height, Matrix4x4 view_matrix, Matrix4x4 projection_matrix) {
	constant shaderNumbers;

	mIconMatrix.setIdentity();
	mIconMatrix.scale(mLocalScale);
	faceSceneCamera(SceneCameraManager::getInstance()->getSceneCamera()->getLocalPosition());
	mIconMatrix.translate(mLocalPosition);

	shaderNumbers.worldMatrix = mIconMatrix;
	shaderNumbers.viewMatrix = view_matrix;
	shaderNumbers.projectionMatrix = projection_matrix;
	shaderNumbers.coefficient = 0.5f * (sin(mElapsedTime) + 1.f);

	mConstantBuffer->update(AGraphicsEngine::getInstance()->getImmediateDeviceContext(), &shaderNumbers);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(mConstantBuffer, mVertexShader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(mConstantBuffer, mPixelShader);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(mVertexShader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(mPixelShader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(mVertexBuffer);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setTexture(mTexture, mPixelShader);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(mVertexBuffer->getVertexCount(), 0);
}

void GameCamera::onPress(int key) {}

void GameCamera::onRelease(int key) {}

void GameCamera::onMouseMove(const Point delta_position) {}

void GameCamera::onLMBPress(const Point mouse_position) {}

void GameCamera::onLMBRelease(const Point mouse_position) {}

void GameCamera::onRMBPress(const Point mouse_position) {}

void GameCamera::onRMBRelease(const Point mouse_position) {}

void GameCamera::faceSceneCamera(Vector3 scene_camera_position) {
	// Calculate the forward direction (from the gizmo to the camera).
	Vector3 forward = scene_camera_position - mLocalPosition;
	forward.Normalize();

	// Assuming left-handed coordinate system, "up" is (0, 1, 0).
	Vector3 up(0, 1, 0);

	// Calculate the right vector by taking the cross product of "up" and "forward".
	Vector3 right = Vector3::cross(up, forward);
	right.Normalize();

	// Calculate the new "up" vector by taking the cross product of "forward" and "right".
	up = Vector3::cross(forward, right);
	up.Normalize();

	// Create a rotation matrix based on the calculated right, up, and forward vectors.
	Matrix4x4 rotationMatrix;
	rotationMatrix.setRightVector(right);
	rotationMatrix.setUpVector(up);
	rotationMatrix.setForwardVector(forward);

	// Apply this rotation to the icon's matrix.
	mIconMatrix *= rotationMatrix;
}