#pragma once

#include <iostream>
#include "UINames.h"

#include "AUIScreen.h"
#include "GraphicsEngine.h"
#include "GameObjectManager.h"

class ToolBar: public AUIScreen
{
public:
	ToolBar(std::string name);
	~ToolBar();

	void drawUI() override;

private:
	
};

