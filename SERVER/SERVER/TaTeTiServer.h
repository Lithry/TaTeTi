#ifndef TATETISERVER_H
#define TATETISERVER_H

#include <iostream>
#include "UDP.h"

class TaTeTiServer{
public:
	TaTeTiServer();
	~TaTeTiServer();
	bool init();
	bool run();
	
private:
	bool waitingForPlayer();
	bool play();
	void makeAMove(char place, char player);
	bool giveBoard();


	std::string player1Id;
	char player1;
	std::string player2Id;
	char player2;
	UDP server;
	std::string data;
	bool waitingForPlayers;
	bool playing;
	bool turnPlayer1;

	char** board;

};
#endif