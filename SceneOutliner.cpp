#include "SceneOutliner.h"

SceneOutliner::SceneOutliner(std::string name) : AUIScreen(name)
{
}

SceneOutliner::~SceneOutliner()
{
}

void SceneOutliner::drawUI()
{
	ImGui::Begin("Scene Outliner");

	for (int i = 0; i < GameObjectManager::getInstance()->getAllObjects().size(); i++)
	{
		if (ImGui::Button(GameObjectManager::getInstance()->getAllObjects()[i]->getName().c_str()))
		{
			GameObjectManager::getInstance()->setSelectedObject(GameObjectManager::getInstance()->getAllObjects()[i]);
		}
	}
	
	ImGui::End();
}
