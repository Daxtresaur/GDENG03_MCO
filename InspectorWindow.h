#pragma once

#include <iostream>
#include "UINames.h"

#include "AUIScreen.h"
#include "GraphicsEngine.h"
#include "GameObjectManager.h"

class InspectorWindow : public AUIScreen
{
public:
	InspectorWindow(std::string name);
	~InspectorWindow();

	void drawUI() override;

private:

	

};

