#ifndef TATETICLIENT_H
#define TATETICLIENT_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <conio.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "192.168.0.10"  //ip address of udp server
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data

class TatetiClient{
public:
	TatetiClient();
	~TatetiClient();
	void SetServerIp();
	bool Init();
	bool Run();
private:
	bool Prepare();
	bool IsReady();
	bool GetBoard();
	void ShowBoard();
	bool TurnOf();
	bool MakeMove();
	bool GetWinner();
	bool UDPConnect(std::string messageToSend);
	void WriteMessage(char(&message)[BUFLEN], std::string messageToSend);
	void interpretMessage(std::string reply);

	std::string serverIp;
	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];
	WSADATA wsa;
	
	bool running;
	char player;
	char turnOf;
	char lastTurnOf;
	bool waitingPlayers;
	bool gameGoing;
	bool winner;
	char playerWinner;
	bool draw;



	char** board;
	char** lastBoard;

	char b1;
	char b2;
	char b3;
	char b4;
	char b5;
	char b6;
	char b7;
	char b8;
	char b9;
	char b1l;
	char b2l;
	char b3l;
	char b4l;
	char b5l;
	char b6l;
	char b7l;
	char b8l;
	char b9l;



	void clearScreen(HANDLE hConsole);
	void CrearKeyboardBuffer();
	HANDLE screen;
};
#endif