#ifndef UDP_H
#define UDP_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data

class UDP{
public:
	UDP();
	~UDP();
	bool init();
	bool waitingForData(std::string& data);
	bool reply(std::string r);
	std::string getLastIp();
private:
	bool createSocket();
	bool prepareStructure();
	bool bindSocket();
	SOCKET s;
	struct sockaddr_in server, si_other;
	int slen, recv_len;
	char buf[BUFLEN];
	WSADATA wsa;
	bool onComunication;
	std::string lastIp;
};
#endif