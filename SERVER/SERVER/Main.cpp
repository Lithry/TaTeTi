#include "TaTeTiServer.h"

int main(){

	TaTeTiServer* game = new TaTeTiServer();
	if (!game->init()){
		exit(EXIT_FAILURE);
	}

	if (!game->run()){
		exit(EXIT_FAILURE);
	}

	return 0;
}