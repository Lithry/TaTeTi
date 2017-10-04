#include "TatetiClient.h"

#include <iostream>
#include <string>
#include <cstring>

TatetiClient::TatetiClient(){}

TatetiClient::~TatetiClient(){
	closesocket(s);
	WSACleanup();
}

bool TatetiClient::Init(){
	screen = GetStdHandle(STD_OUTPUT_HANDLE);

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return false;
	}
	printf("Initialised.\n");

	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		return false;
	}

	//setup address structure
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	running = true;
	return true;
}

bool TatetiClient::Run(){
	while (running){
		clearScreen(screen);


		GetBoard();
		TurnOf();
		
		std::cout << "\n Turno de " << turnOf << std::endl << std::endl;
		ShowBoard();

		getWinner();


		MakeMove();

		if (gameGoing && !gameOver){
			playMove();
		}
		

	}

	return true;
}

bool TatetiClient::GetBoard(){
	if (!UDPConnect("B"))
		return false;
}

void TatetiClient::ShowBoard(){
	for (size_t i = 0; i < 3; i++){
		switch (i){
		case 1:
			std::cout << '\t' << "-----------" << std::endl << '\t';
			break;
		case 2:
			std::cout << '\t' << "-----------" << std::endl << '\t';
			break;
		default:
			std::cout << '\t';
			break;
		}
		for (size_t j = 0; j < 3; j++){
			switch (j){
			case 0:
				std::cout << ' ' << board[i][j] << " |";
				break;
			case 1:
				std::cout << ' ' << board[i][j] << " |";
				break;
			default:
				std::cout << ' ' << board[i][j];
				break;
			}

		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool TatetiClient::TurnOf(){
	if (!UDPConnect("T"))
		return false;
}

bool TatetiClient::MakeMove(){
	int move = 0;

	std::cout << " Use de Numpad to chose a position: ";
	std::cin.clear();
	fflush(stdin);
	std::cin >> move;

	switch (move){
	case 1:
		if (!UDPConnect("P1" + player))
			return false;
		break;
	case 2:
		if (!UDPConnect("P2" + player))
			return false;
		break;
	case 3:
		if (!UDPConnect("P3" + player))
			return false;
		break;
	case 4:
		if (!UDPConnect("P4" + player))
			return false;
		break;
	case 5:
		if (!UDPConnect("P5" + player))
			return false;
		break;
	case 6:
		if (!UDPConnect("P6" + player))
			return false;
		break;
	case 7:
		if (!UDPConnect("P7" + player))
			return false;
		break;
	case 8:
		if (!UDPConnect("P8" + player))
			return false;
		break;
	case 9:
		if (!UDPConnect("P9" + player))
			return false;
		break;
	}

	return true;
}

bool TatetiClient::UDPConnect(std::string messageToSend){
	WriteMessage(message, messageToSend);

	//send the message
	if (sendto(s, message, strlen(message), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		return false;
	}

	//receive a reply and print it
	//clear the buffer by filling null, it might have previously received data
	memset(buf, '\0', BUFLEN);
	//try to receive some data, this is a blocking call
	if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
	{
		printf("recvfrom() failed with error code : %d", WSAGetLastError());
		return false;
	}

	interpretMessage(buf);

	return true;
}

void TatetiClient::WriteMessage(char(&message)[BUFLEN], std::string messageToSend){
	for (size_t i = 0; i < BUFLEN; i++){
		if (i < messageToSend.length())
			message[i] = messageToSend[i];
		else if (i == BUFLEN - 1)
			message[i] = '\0';
		else
			message[i] = ' ';
	}
}

void TatetiClient::interpretMessage(std::string reply){
	if (reply[0] == 'B'){
		board[0][0] = reply[1];
		board[0][1] = reply[2];
		board[0][2] = reply[3];
		board[1][0] = reply[4];
		board[1][1] = reply[5];
		board[1][2] = reply[6];
		board[2][0] = reply[7];
		board[2][2] = reply[8];
		board[2][3] = reply[9];
	}
	
	if (reply[0] == 'T')
		turnOf = reply[1];
}










void Game::clearScreen(HANDLE hConsole){
	COORD coordScreen = { 0, 0 };    // home for the cursor 
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	// Get the number of character cells in the current buffer. 

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire screen with blanks.

	if (!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten))
		return;

	// Get the current text attribute.

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;

	// Set the buffer's attributes accordingly.

	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten))
		return;

	// Put the cursor at its home coordinates.

	SetConsoleCursorPosition(hConsole, coordScreen);
}