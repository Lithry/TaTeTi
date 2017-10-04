#ifndef TATETICLIENT_H
#define TATETICLIENT_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>

#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "192.168.0.10"  //ip address of udp server
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data

class TatetiClient{
public:
	TatetiClient();
	~TatetiClient();
	bool Init();
	bool Run();
private:
	bool GetBoard();
	void ShowBoard();
	bool TurnOf();
	bool MakeMove();
	bool UDPConnect(std::string messageToSend);
	void WriteMessage(char(&message)[BUFLEN], std::string messageToSend);
	void interpretMessage(std::string reply);

	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];
	WSADATA wsa;
	
	bool running;
	char** board;
	char player;
	char turnOf;


	void clearScreen(HANDLE hConsole);
	HANDLE screen;
};
#endif