#pragma once

#include <iostream>
#include "UINames.h"

#include "AUIScreen.h"
#include "GraphicsEngine.h"
#include "GameObjectManager.h"
class EngineProfiler : public AUIScreen
{
public:
	EngineProfiler(std::string name);
	~EngineProfiler();

	void drawUI() override;

	
};

