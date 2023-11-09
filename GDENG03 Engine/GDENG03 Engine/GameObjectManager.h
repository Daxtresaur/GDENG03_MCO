#pragma once
#include"AGameObject.h"
#include<string>
#include<vector>
#include<unordered_map>
#include"AVertexShader.h"
#include"APixelShader.h"
#include"GameCamera.h"

class GameObjectManager
{
public:

	enum PrimitiveType {
		CUBE,
		PLANE,
		GAME_CAMERA
	};

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(std::string name);
	std::vector<AGameObject*> getAllGameObjects();
	int getObjectCount();
	void update();
	void render(int viewport_width, int viewport_height);
	void renderToGameCamera(int viewport_width, int viewport_height, GameCamera* game_camera);
	void addObject(AGameObject* game_object);
	void createObject(PrimitiveType primitive_type);
	void deleteObject(AGameObject* game_object);
	void deleteObjectByName(std::string name);

	void setSelectedObject(std::string name);
	void setSelectedObject(AGameObject* game_object);
	AGameObject* getSelectedObject();
	void deselectObject();

	bool isCameraSelected();
	GameCamera* getSelectedCamera();

	void setCurrentCamera(GameCamera* game_camera);
	GameCamera* getCurrentCamera();

private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator =(GameObjectManager const&) {};
	static GameObjectManager* instance;

	std::vector<AGameObject*> mGameObjectList;
	std::unordered_map<std::string, AGameObject*> mGameObjectTable;
	std::unordered_map<std::string, GameCamera*> mCameraTable;

	AGameObject* mCurrentSelectedObject = nullptr;
	GameCamera* mCurrentGameCamera = nullptr;
};