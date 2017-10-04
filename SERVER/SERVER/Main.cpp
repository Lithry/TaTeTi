#include <iostream>

#include "TatetiServer.h"

void main(){
	TatetiServer tateti;

	if (!tateti.Init()){
		std::cin.clear();
		fflush(stdin);
		std::cin.get();
		exit(EXIT_FAILURE);
	}

	if (!tateti.UDPConnect()){
		std::cin.clear();
		fflush(stdin);
		std::cin.get();
		exit(EXIT_FAILURE);
	}
}