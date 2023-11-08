#include"GameObjectManager.h"
#include"TimeManager.h"
#include"ACube.h"
#include"APlane.h"
#include"GlobalProperties.h"
#include"AGraphicsEngine.h"
#include<iostream>
#include"SceneCameraManager.h"

GameObjectManager* GameObjectManager::instance = nullptr;

GameObjectManager* GameObjectManager::getInstance() {
	return instance;
}

void GameObjectManager::initialize() {
	instance = new GameObjectManager();
}

void GameObjectManager::destroy() {
	instance->mCameraTable.clear();
	instance->mGameObjectTable.clear();

	for (int i = 0; i < instance->mGameObjectList.size(); i++) {
		delete instance->mGameObjectList[i];
	}
}

AGameObject* GameObjectManager::findObjectByName(std::string name) {
	return mGameObjectTable[name];
}

std::vector<AGameObject*> GameObjectManager::getAllGameObjects() {
	return mGameObjectList;
}

int GameObjectManager::getObjectCount() {
	return mGameObjectList.size();
}

int GameObjectManager::getActiveObjectCount() {
	int activeObjectCount = 0;
	for (int i = 0; i < mGameObjectList.size(); i++) {
		if (mGameObjectList[i]->isActive()) activeObjectCount++;
	}
	return activeObjectCount;
}

void GameObjectManager::update() {
	for (int i = 0; i < mGameObjectList.size(); i++) {
		if (mGameObjectList[i]->isActive()) mGameObjectList[i]->update(TimeManager::getDeltaTime());
	}
}

void GameObjectManager::render(int viewport_width, int viewport_height, AVertexShader* vertex_shader, APixelShader* pixel_shader) {
	for (int i = 0; i < mGameObjectList.size(); i++) {
		if (mGameObjectList[i]->isActive()) mGameObjectList[i]->draw(
			viewport_width,
			viewport_height,
			vertex_shader,
			pixel_shader,
			SceneCameraManager::getInstance()->getSceneCameraViewMatrix(),
			SceneCameraManager::getInstance()->getSceneCameraProjectionMatrix()
		);
	}
}

void GameObjectManager::renderToGameCamera(int viewport_width, int viewport_height, AVertexShader* vertex_shader, APixelShader* pixel_shader, GameCamera* game_camera) {
	for (int i = 0; i < mGameObjectList.size(); i++) {
		if (mGameObjectList[i]->isActive()) mGameObjectList[i]->draw(
			viewport_width,
			viewport_height,
			vertex_shader,
			pixel_shader,
			game_camera->getViewMatrix(),
			game_camera->getProjectionMatrix()
		);
	}
}

void GameObjectManager::addObject(AGameObject* game_object) {
	mGameObjectList.push_back(game_object);
	mGameObjectTable[game_object->getObjectName()] = game_object;
}

void GameObjectManager::createObject(PrimitiveType primitive_type, void* shader_byte_code, size_t shader_size) {
	std::string newName = "";

	switch (primitive_type) {
	case CUBE: {
		int cubeCount = -1;
		AGameObject* cube = nullptr;
		do {
			cubeCount++;
			newName = "Cube " + std::to_string(cubeCount);
			cube = mGameObjectTable[newName];
		}
		while (cube);

		ACube* newCube = new ACube(newName, shader_byte_code, shader_size);
		addObject(newCube);
		std::cout << newCube->getObjectName() << " spawned." << std::endl;
	}
	break;

	case PLANE: {
		int planeCount = -1;
		AGameObject* plane = nullptr;
		do {
			planeCount++;
			newName = "Plane " + std::to_string(planeCount);
			plane = mGameObjectTable[newName];
		}
		while (plane);

		APlane* newPlane = new APlane(newName, shader_byte_code, shader_size);
		addObject(newPlane);
		std::cout << newPlane->getObjectName() << " spawned." << std::endl;
	}
	break;

	case GAME_CAMERA: {
		int cameraCount = -1;
		AGameObject* camera = nullptr;
		do {
			cameraCount++;
			newName = "Camera " + std::to_string(cameraCount);
			camera = mGameObjectTable[newName];
		} while (camera);

		GameCamera* newCamera = new GameCamera(newName, shader_byte_code, shader_size);
		addObject(newCamera);
		mCameraTable[newName] = newCamera;
		std::cout << newCamera->getObjectName() << " spawned." << std::endl;
	}
	break;

	}
}

void GameObjectManager::createObject(PrimitiveType primitive_type) {
	std::string newName = "";
	void* shaderByteCode = nullptr;
	size_t shaderSize = 0;

	switch (primitive_type) {
	case CUBE: {
		int cubeCount = -1;
		AGameObject* cube = nullptr;
		do {
			cubeCount++;
			newName = "Cube " + std::to_string(cubeCount);
			cube = mGameObjectTable[newName];
		}
		while (cube);

		AGraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &shaderSize);
		ACube* newCube = new ACube(newName, shaderByteCode, shaderSize);
		addObject(newCube);
		std::cout << newCube->getObjectName() << " spawned." << std::endl;
		AGraphicsEngine::getInstance()->releaseCompiledVertexShader();
	}
	break;

	case PLANE: {
		int planeCount = -1;
		AGameObject* plane = nullptr;
		do {
			planeCount++;
			newName = "Plane " + std::to_string(planeCount);
			plane = mGameObjectTable[newName];
		}
		while (plane);

		AGraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &shaderSize);
		APlane* newPlane = new APlane(newName, shaderByteCode, shaderSize);
		addObject(newPlane);
		std::cout << newPlane->getObjectName() << " spawned." << std::endl;
		AGraphicsEngine::getInstance()->releaseCompiledVertexShader();
	}
	break;

	case GAME_CAMERA: {
		int cameraCount = -1;
		AGameObject* camera = nullptr;
		do {
			cameraCount++;
			newName = "Camera " + std::to_string(cameraCount);
			camera = mGameObjectTable[newName];
		} while (camera);

		AGraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &shaderSize);
		GameCamera* newCamera = new GameCamera(newName, shaderByteCode, shaderSize);
		addObject(newCamera);
		mCameraTable[newName] = newCamera;
		std::cout << newCamera->getObjectName() << " spawned." << std::endl;
		AGraphicsEngine::getInstance()->releaseCompiledVertexShader();
	}
	break;

	}
}

void GameObjectManager::deleteObject(AGameObject* game_object) {
	std::string key = game_object->getObjectName();
	if (mCameraTable[key]) mCameraTable.erase(key);
	mGameObjectTable.erase(key);
	mGameObjectList.erase(std::remove(mGameObjectList.begin(), mGameObjectList.end(), game_object), mGameObjectList.end());
	mGameObjectList.shrink_to_fit();
	delete game_object;
}

void GameObjectManager::deleteObjectByName(std::string name) {
	AGameObject* object = findObjectByName(name);
	if (object) deleteObject(object);
}

void GameObjectManager::setSelectedObject(std::string name) {
	if (mCurrentSelectedObject) mCurrentSelectedObject->deselect();
	AGameObject* object = findObjectByName(name);
	if (object) {
		mCurrentSelectedObject = object;
		object->select();
	}
}

void GameObjectManager::setSelectedObject(AGameObject* game_object) {
	if (mCurrentSelectedObject) mCurrentSelectedObject->deselect();
	mCurrentSelectedObject = game_object;
	game_object->select();
}

AGameObject* GameObjectManager::getSelectedObject() {
	return mCurrentSelectedObject;
}

void GameObjectManager::deselectObject() {
	if (mCurrentGameCamera == mCurrentSelectedObject) {
		mCurrentGameCamera = nullptr;
	}

	if (mCurrentSelectedObject) {
		mCurrentSelectedObject->deselect();
		mCurrentSelectedObject = nullptr;
	}
}

bool GameObjectManager::isCameraSelected() {
	if (!mCurrentSelectedObject) return false;

	std::string currentObjectName = mCurrentSelectedObject->getObjectName();
	GameCamera* camera = mCameraTable[currentObjectName];
	if (!camera) return false;

	return true;
}

GameCamera* GameObjectManager::getSelectedCamera() {
	if (isCameraSelected()) {
		std::string currentObjectName = mCurrentSelectedObject->getObjectName();
		GameCamera* camera = mCameraTable[currentObjectName];
		if (camera != mCurrentGameCamera) setCurrentCamera(camera);
		return camera;
	}

	else return nullptr;
}

void GameObjectManager::setCurrentCamera(GameCamera* game_camera) {
	mCurrentGameCamera = game_camera;
}

GameCamera* GameObjectManager::getCurrentCamera() {
	return mCurrentGameCamera;
}

GameObjectManager::GameObjectManager() {
	mCurrentSelectedObject = nullptr;
}

GameObjectManager::~GameObjectManager() {
	delete instance;
}