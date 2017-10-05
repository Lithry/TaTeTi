#include <iostream>

#include "TatetiClient.h"

void main(){
	TatetiClient client;

	if (!client.Init()){
		std::cin.sync();
		std::cin.clear();
		std::cin.ignore(255, '\n');
		fflush(stdin);
		std::cin.get();
		exit(EXIT_FAILURE);
	}

	if (!client.Run()){
		std::cin.sync();
		std::cin.clear();
		std::cin.ignore(255, '\n');
		fflush(stdin);
		std::cin.get();
		exit(EXIT_FAILURE);
	}

	std::cin.sync();
	std::cin.clear();
	std::cin.ignore(255, '\n');
	fflush(stdin);
	std::cin.get();

}