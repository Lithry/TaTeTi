#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <chrono>
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "192.168.0.10"  //ip address of udp server
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
	bool wantToPlay();
	bool sendMessage(std::string data);
	std::string receiveReplay();
	void playMove();
	bool winer();
	void clearScreen(HANDLE hConsole);
	bool gameGoing;
	bool gameOver;
	bool playing;
	HANDLE screen;
	char** board;
	char player;
	char turnOf;
	float timer;

	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];
	WSADATA wsa;
	std::string reply;
};
#endif