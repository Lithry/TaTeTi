#include <iostream>

#include "TatetiClient.h"

void main(){
	TatetiClient client;

	if (!client.Init()){
		std::cin.clear();
		fflush(stdin);
		std::cin.get();
		exit(EXIT_FAILURE);
	}

	if (!client.Run()){
		std::cin.clear();
		fflush(stdin);
		std::cin.get();
		exit(EXIT_FAILURE);
	}

	std::cin.clear();
	std::cin.ignore();
	fflush(stdin);
	std::cin.get();

}