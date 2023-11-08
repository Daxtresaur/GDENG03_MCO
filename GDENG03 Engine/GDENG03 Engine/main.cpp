/*
Group 4: Camera as a Modifiable Game Object
GDENG03 X22
MCO: Game Engine Feature Replication
*/

#include"AppWindow.h"
#include"GameViewWindow.h"

int main() {
	AppWindow scene;
	GameViewWindow game;

	if (scene.initialize() && game.initialize()) {
		while (scene.isRunning()) {
			scene.broadcast();
			game.broadcast();
		}
		game.onDestroy();
		game.release();
	}

	return 0;
}