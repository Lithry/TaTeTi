#include "UDP.h"

UDP::UDP(){}

UDP::~UDP(){
	closesocket(s);
	WSACleanup();
}

bool UDP::init(){
	slen = sizeof(si_other);

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return false;
	}
	printf("Initialised.\n");

	if (!createSocket())
		return false;

	if (!prepareStructure())
		return false;


	if (!bindSocket())
		return false;
	
	onComunication = true;

	return true;
}

bool UDP::createSocket(){
	//Create a socket
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
		return false;
	}
	printf("Socket created.\n");
	return true;
}

bool UDP::prepareStructure(){
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	return true;
}

bool UDP::bindSocket(){
	//Bind
	if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		return false;
	}
	puts("Bind done");
	return true;
}

bool UDP::waitingForData(std::string& data){
	while (onComunication)
	{

		printf("Waiting for data...");
		fflush(stdout);

		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);

		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			return false;
		}

		//print details of the client/peer and the data received
		printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		printf("Data: %s\n", buf);

		data = buf;
		lastIp = inet_ntoa(si_other.sin_addr);
	}

	return true;
}

bool UDP::reply(std::string r){
	//now reply the client with the same data
	for (size_t i = 0; i < r.length(); i++)
	{
		buf[i] = r[i];
	}
	buf[r.length()] = '\0';

	if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		return false;
	}
}

std::string UDP::getLastIp(){
	return lastIp;
}