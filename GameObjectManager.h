#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "AGameObject.h"
#include "EngineTime.h"
#include "Cube.h"
#include "Quad.h"

class GameObjectManager
{
public:
	typedef std::vector <AGameObject*> List;
	typedef std::unordered_map<std::string, AGameObject*> HashTable;

	enum PrimitiveType {
		CUBE,
		PLANE,
		SPHERE
	};

	GameObjectManager();
	~GameObjectManager();

	static GameObjectManager* getInstance();
	static void initialize();
	void destroy();

	AGameObject* findObjectByName(string name);
	List getAllObjects();
	int activeObjects();
	void updateAll();
	void renderAll(int viewportWidth, int viewportHeight, VertexShader* vs, PixelShader* ps);
	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(string name);
	void setSelectedObject(string name);
	void setSelectedObject(AGameObject* gameObject);
	AGameObject* getSelectedObject();

private:
	static GameObjectManager* sharedInstance;
	AGameObject* selectedGameObject = nullptr;

	List gameObjectList;
	HashTable hT;
};

