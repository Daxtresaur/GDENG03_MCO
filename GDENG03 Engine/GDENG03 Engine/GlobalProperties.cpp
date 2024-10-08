#include"GlobalProperties.h"

int GlobalProperties::WINDOW_WIDTH = 1280;
int GlobalProperties::WINDOW_HEIGHT = 720;
int GlobalProperties::GAME_VIEW_WIDTH = 853;
int GlobalProperties::GAME_VIEW_HEIGHT = 480;

bool GlobalProperties::IS_CUBE_MOVEMENT_ON = true;
bool GlobalProperties::ARE_CUBES_ACTIVE = true;
float GlobalProperties::BACKGROUND_COLOR[3] = {
	154.f / 255.f,
	216.f / 255.f,
	216.f / 255.f
};

void GlobalProperties::setActiveCubes(bool flag) {
	IS_CUBE_MOVEMENT_ON = flag;
}

void GlobalProperties::setEnabledCubes(bool flag) {
	ARE_CUBES_ACTIVE = flag;
}

void GlobalProperties::setBackgroundColor(float red, float green, float blue) {
	BACKGROUND_COLOR[0] = red;
	BACKGROUND_COLOR[1] = green;
	BACKGROUND_COLOR[2] = blue;
}