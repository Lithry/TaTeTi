#include "Game.h"

int main(){
	Game* game = new Game();

	game->init();
	game->play();

	return 0;
}