/*
Group 4: Camera as a Modifiable Game Object
GDENG03 X22
MCO: Game Engine Feature Replication
*/

#include"AppWindow.h"

int main() {
	AppWindow game;

	if (game.initialize()) {
		while (game.isRunning()) {
			game.broadcast();
		}
	}

	return 0;
}