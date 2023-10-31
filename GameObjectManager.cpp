#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::sharedInstance = nullptr;

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{

}

GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager();
}

void GameObjectManager::destroy()
{
	for (int i = 0; i < gameObjectList.size(); i++) 
	{
		gameObjectList[i]->release();
	}

	gameObjectList.clear();
	hT.clear();
	sharedInstance = nullptr;
}

AGameObject* GameObjectManager::findObjectByName(string name)
{
	return hT[name];
}

GameObjectManager::List GameObjectManager::getAllObjects()
{
	return gameObjectList;
}

int GameObjectManager::activeObjects()
{
	int active = 0;

	for (int i = 0; i < gameObjectList.size(); i++)
	{
		if (gameObjectList[i]->getActive() == true) 
		{
			active++;
		}
	}
	return active;
}

void GameObjectManager::updateAll()
{
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		if(gameObjectList[i]->getActive())
		gameObjectList[i]->update(EngineTime::getDeltaTime());
	}
}

void GameObjectManager::renderAll(int viewportWidth, int viewportHeight, VertexShader* vs, PixelShader* ps)
{
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		if (gameObjectList[i]->getActive())
		gameObjectList[i]->draw(viewportWidth,viewportHeight, vs,ps);
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	gameObjectList.push_back(gameObject);
	hT.insert({ gameObject->getName(),gameObject });
}

void GameObjectManager::createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader)
{
	switch (type)
	{
	case CUBE: {
		
		Cube* newCube = new Cube("cubeobject",shaderByteCode,sizeShader);
		GameObjectManager::getInstance()->addObject(newCube);
		break;}
	case PLANE: {

		Quad* newPlane = new Quad("planeobject", shaderByteCode, sizeShader);
		GameObjectManager::getInstance()->addObject(newPlane); break;}
	case SPHERE:{break;}
	}
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{

}

void GameObjectManager::deleteObjectByName(string name)
{
	hT.erase(name);
}

void GameObjectManager::setSelectedObject(string name)
{
	selectedGameObject = hT[name];
}

void GameObjectManager::setSelectedObject(AGameObject* gameObject)
{
	selectedGameObject = gameObject;
}

AGameObject* GameObjectManager::getSelectedObject()
{
	return selectedGameObject;
}
