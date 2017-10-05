#include "TatetiServer.h"

TatetiServer::TatetiServer(){

}

TatetiServer::~TatetiServer(){
	closesocket(s);
	WSACleanup();
}

bool TatetiServer::Init(){
	slen = sizeof(si_other);

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return false;
	}
	printf("Initialised.\n");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
		return false;
	}
	printf("Socket created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	//Bind
	if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		return false;
	}
	puts("Bind done");

	// Cosas del TaTeTi
	char a[][3] = { { '7', '8', '9' },
					{ '4', '5', '6' },
					{ '1', '2', '3' }
	};
	board = new char*[3];
	for (size_t i = 0; i < 3; i++)
	{
		board[i] = new char[3];
	}

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			board[i][j] = a[i][j];
		}
	}

	player1Ip = "";
	player2Ip = "";
	running = true;
	turn1 = true;

	return true;
}

bool TatetiServer::UDPConnect(){
	while (running)
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
		
		lastIp = inet_ntoa(si_other.sin_addr);
		std::string reply = interpretMessage(buf);

		for (size_t i = 0; i < reply.length(); i++)
		{
			buf[i] = reply[i];
		}
		buf[reply.length()] = '\0';

		//now reply the client with the same data
		if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			return false;
		}
	}

	return true;
}

std::string TatetiServer::interpretMessage(std::string m){
	if (m[0] == '1')
		return SetPlayer();
	
	if (m[0] == 'T')
		return TurnOf();
	
	if (m[0] == 'G')
		return PlayersSets();
	
	if (m[0] == 'B')
		return GetBoard();
	
	if (m[0] == 'P')
		return MakeMove(m[1], m[2]);
	
	if (m[0] == 'W')
		return Winner();

	return "";
}

std::string TatetiServer::SetPlayer(){
	if (player1Ip == ""){
		player1Ip = lastIp;
		return "1X";
	}
	else if (player2Ip == ""){
		player2Ip = lastIp;
		return "1O";
	}
	else if (player1Ip != "" && player2Ip != ""){
		return "10";
	}
}

std::string TatetiServer::PlayersSets(){
	if (player1Ip != "" && player2Ip != "")
		return "G1";
	else
		return "G0";
}

std::string TatetiServer::TurnOf(){
	if (turn1)
		return "TX";
	else
		return "TO";
}

std::string TatetiServer::GetBoard(){
	std::string boardReturn = "B";

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			boardReturn += board[i][j];
		}
	}

	return boardReturn;
}

std::string TatetiServer::MakeMove(char pos, char player){
	if ((turn1 && player == 'X') || (!turn1 && player == 'O')){
		switch (pos){
		case '1':
			if (board[2][0] != 'X' && board[2][0] != 'O'){
				board[2][0] = player;
				turn1 = (turn1) ? false : true;
				return "R";
			}
			break;
		case '2':
			if (board[2][1] != 'X' && board[2][1] != 'O'){
				board[2][1] = player;
				turn1 = (turn1) ? false : true;
				return "R";
			}
			break;
		case '3':
			if (board[2][2] != 'X' && board[2][2] != 'O'){
				board[2][2] = player;
				turn1 = (turn1) ? false : true;
				return "R";
			}
			break;
		case '4':
			if (board[1][0] != 'X' && board[1][0] != 'O'){
				board[1][0] = player;
				turn1 = (turn1) ? false : true;
				return "R";
			}
			break;
		case '5':
			if (board[1][1] != 'X' && board[1][1] != 'O'){
				board[1][1] = player;
				turn1 = (turn1) ? false : true;
				return "R";
			}
			break;
		case '6':
			if (board[1][2] != 'X' && board[1][2] != 'O'){
				board[1][2] = player;
				turn1 = (turn1) ? false : true;
				return "R";
			}
			break;
		case '7':
			if (board[0][0] != 'X' && board[0][0] != 'O'){
				board[0][0] = player;
				turn1 = (turn1) ? false : true;
				return "R";
			}
			break;
		case '8':
			if (board[0][1] != 'X' && board[0][1] != 'O'){
				board[0][1] = player;
				turn1 = (turn1) ? false : true;
				return "R";
			}
			break;
		case '9':
			if (board[0][2] != 'X' && board[0][2] != 'O'){
				board[0][2] = player;
				turn1 = (turn1) ? false : true;
				return "R";
			}
			break;
		}
	}
	return "";
}

std::string TatetiServer::Winner(){
	bool draw = true;
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (board[i][j] != 'X' && board[i][j] != 'O')
				draw = false;
		}
	}

	if (draw)
		return "WD";
	else{
		for (size_t i = 0; i < 3; i++)
		{
			if (board[i][0] == board[i][1] && board[i][1] == board[i][2]){
				std::string r = "W";
				r += board[i][0];
				return r;
			}
		}

		for (size_t i = 0; i < 3; i++)
		{
			if (board[0][i] == board[1][i] && board[1][i] == board[2][i]){
				std::string r = "W";
				r += board[0][i];
				return r;
			}
		}

		if (board[0][0] == board[1][1] && board[1][1] == board[2][2]){
			std::string r = "W";
			r += board[0][0];
			return r;
		}
		else if (board[0][2] == board[1][1] && board[1][1] == board[2][0]){
			std::string r = "W";
			r += board[0][2];
			return r;
		}
	}

	return "W0";
}