#pragma once

#include <iostream>
#include "UINames.h"

#include "AUIScreen.h"
#include "GraphicsEngine.h"
#include "GameObjectManager.h"

class SceneOutliner : public AUIScreen
{
public:
	SceneOutliner(std::string name);
	~SceneOutliner();

	void drawUI() override;

private:

	


};

