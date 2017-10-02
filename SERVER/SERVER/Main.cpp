#include "UDP.h"

int main(){

	UDP* server = new UDP();
	if (!server->init()){
		exit(EXIT_FAILURE);
	}

	if (!server->communication()){
		exit(EXIT_FAILURE);
	}

	return 0;
}