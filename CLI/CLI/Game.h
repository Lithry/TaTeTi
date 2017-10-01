#ifndef GAME_H
#define GAME_H

#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "127.0.0.1"  //ip address of udp server
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data

#include <Windows.h>

class Game{
public:
	Game();
	~Game();
	bool init();
	bool play();
private:
	bool connectToServer();
	void checkEnemyMove();
	bool playMoveX();
	bool playMoveO();
	bool winer();
	void clearScreen(HANDLE hConsole);
	bool gameGoing;
	bool gameOver;
	bool playing;
	HANDLE screen;
	char** board;
	char** lastMoveBoard;
	char turn;
};
#endif