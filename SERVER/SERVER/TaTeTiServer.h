#ifndef TATETISERVER_H
#define TATETISERVER_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data

class TatetiServer{
public:
	TatetiServer();
	~TatetiServer();
	bool Init();
	bool UDPConnect();
private:
	std::string interpretMessage(std::string m);
	
	std::string SetPlayer();
	std::string PlayersSets();
	std::string TurnOf();
	std::string GetBoard();
	std::string MakeMove(char pos, char player);
	std::string Winner();


	bool turn1;
	char** board;
	std::string lastIp;
	std::string player1Ip;
	std::string player2Ip;


	SOCKET s;
	struct sockaddr_in server, si_other;
	int slen, recv_len;
	char buf[BUFLEN];
	WSADATA wsa;
	bool running;
};
#endif