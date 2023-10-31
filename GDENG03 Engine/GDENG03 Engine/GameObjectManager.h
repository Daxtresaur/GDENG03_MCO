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
	int getActiveObjectCount();
	void update();
	void render(int viewport_width, int viewport_height, AVertexShader* vertex_shader, APixelShader* pixel_shader);
	void addObject(AGameObject* game_object);
	void createObject(PrimitiveType primitive_type, void* shader_byte_code, size_t shader_size);
	void createObject(PrimitiveType primitive_type);
	void deleteObject(AGameObject* game_object);
	void deleteObjectByName(std::string name);

	void setSelectedObject(std::string name);
	void setSelectedObject(AGameObject* game_object);
	AGameObject* getSelectedObject();
	void deselectObject();

	GameCamera* getSelectedCamera();

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
};