#include "TatetiClient.h"

#include<limits>

TatetiClient::TatetiClient(){}

TatetiClient::~TatetiClient(){
	closesocket(s);
	WSACleanup();
	CrearKeyboardBuffer();
}

void TatetiClient::SetServerIp() {
	std::cout << " Ingrese la IP del server: ";
	std::cin.clear();
	fflush(stdin);
	std::cin >> serverIp;
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
	printf(" Ingrese la PORT del server: ");
	gets_s(message);
	si_other.sin_port = htons((unsigned short)strtoul(message, NULL, 0));
	printf(" Ingrese la IP del server: ");
	gets_s(message);
	si_other.sin_addr.S_un.S_addr = inet_addr(message);
	//si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	player = '0';
	running = true;
	waitingPlayers = true;
	gameGoing = false;
	winner = false;
	draw = false;
	return true;
}

bool TatetiClient::Run(){
	while (running){
		
		std::cout << "\n Esperando a Jugadores..." << std::endl << std::endl;
		while (waitingPlayers){
			Prepare();
			IsReady();
		}

		clearScreen(screen);
		TurnOf();
		while (gameGoing){
			GetBoard();
			
			if (turnOf == player)
				MakeMove();
			
			TurnOf();

			GetWinner();
		}

		GetBoard();
		if (winner){
			clearScreen(screen);
			std::cout << "\n Ganador: " << playerWinner << std::endl << std::endl;
			ShowBoard();
			running = false;
		}

		if (draw){
			clearScreen(screen);
			std::cout << "\n Empate!!! " << std::endl << std::endl;
			ShowBoard();
			running = false;
		}
	}

	return true;
}

bool TatetiClient::Prepare() {
	if (player == '0') {
		if (!UDPConnect("1"))
			return false;
	}

	return true;
}

bool TatetiClient::IsReady() {
	if (player != '0') {
		if (!UDPConnect("G"))
			return false;
	}

	return true;
}

bool TatetiClient::GetBoard(){
	if (!UDPConnect("B"))
		return false;

	return true;
}

void TatetiClient::ShowBoard(){
	std::cout << "\t " << b1 << " | " << b2 << " | " << b3 << std::endl;
	std::cout << "\t" << "-----------" << std::endl;
	std::cout << "\t " << b4 << " | " << b5 << " | " << b6 << std::endl;
	std::cout << "\t" << "-----------" << std::endl;
	std::cout << "\t " << b7 << " | " << b8 << " | " << b9 << std::endl;
	std::cout << std::endl;
}

bool TatetiClient::TurnOf(){
	if (!UDPConnect("T"))
		return false;

	return true;
}

bool TatetiClient::MakeMove(){
	int move = 0;
	
	do{
	clearScreen(screen);
	std::cout << "\n Turno de " << turnOf << "\n\nPlayer: " << player << std::endl << std::endl;
	ShowBoard();

	fflush(stdin);
	std::cin.clear();
	
	//std::cin.ignore(INT_MAX, '\n');
	CrearKeyboardBuffer();
	std::cout << " Use de Numpad to chose a position: ";
	
	std::cin >> move;
	if (std::cin.fail()) {
		std::cin.clear();
		fflush(stdin);
		std::cout << " Comando Incorrecto";
		std::cin.ignore(99, '\n');
	}
	} while (move < 1 || move > 9);
	

	std::string message = "P";
	switch (move){
	case 1:
		if (player == 'X')
			message += "1X";
		else
			message += "1O";

		if (!UDPConnect(message))
			return false;
		break;
	case 2:
		if (player == 'X')
			message += "2X";
		else
			message += "2O";

		if (!UDPConnect(message))
			return false;
		break;
	case 3:
		if (player == 'X')
			message += "3X";
		else
			message += "3O";

		if (!UDPConnect(message))
			return false;
		break;
	case 4:
		if (player == 'X')
			message += "4X";
		else
			message += "4O";

		if (!UDPConnect(message))
			return false;
		break;
	case 5:
		if (player == 'X')
			message += "5X";
		else
			message += "5O";

		if (!UDPConnect(message))
			return false;
		break;
	case 6:
		if (player == 'X')
			message += "6X";
		else
			message += "6O";

		if (!UDPConnect(message))
			return false;
		break;
	case 7:
		if (player == 'X')
			message += "7X";
		else
			message += "7O";

		if (!UDPConnect(message))
			return false;
		break;
	case 8:
		if (player == 'X')
			message += "8X";
		else
			message += "8O";

		if (!UDPConnect(message))
			return false;
		break;
	case 9:
		if (player == 'X')
			message += "9X";
		else
			message += "9O";

		if (!UDPConnect(message))
			return false;
		break;
	}

	return true;
}

bool TatetiClient::GetWinner() {
	if (!UDPConnect("W"))
		return false;

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
	if (reply[0] == '1') {
		player = reply[1];
	}

	if (reply[0] == 'G') {
		if (reply[1] == '1') {
			waitingPlayers = false;
			gameGoing = true;
		}
	}
	
	if (reply[0] == 'B'){
		b1 = reply[1];
		b2 = reply[2];
		b3 = reply[3];
		b4 = reply[4];
		b5 = reply[5];
		b6 = reply[6];
		b7 = reply[7];
		b8 = reply[8];
		b9 = reply[9];
		
		if (b1l != b1 || b2l != b2 || b3l != b3 || b4l != b4 || b5l != b5 || b6l != b6 || b7l != b7 || b8l != b8 || b9l != b9) {
			clearScreen(screen);
			std::cout << "\n Turno de " << turnOf << "\n\n Player: " << player << std::endl << std::endl;
			ShowBoard();
			b1l = b1;
			b2l = b2;
			b3l = b3;
			b4l = b4;
			b5l = b5;
			b6l = b6;
			b7l = b7;
			b8l = b8;
			b9l = b9;
		}
	}

	if (reply[0] == 'R') {
		clearScreen(screen);
		std::cout << "\n Turno de " << turnOf << "\n\n Player: " << player << std::endl << std::endl;
		ShowBoard();
	}

	if (reply[0] == 'T') {
		turnOf = reply[1];
		if (turnOf != lastTurnOf) {
			clearScreen(screen);
			std::cout << "\n Turno de " << turnOf << "\n\n Player: " << player << std::endl << std::endl;
			ShowBoard();
			lastTurnOf = turnOf;
		}
	}

	if (reply[0] == 'W') {
		switch (reply[1]){
		case 'X':
			gameGoing = false;
			winner = true;
			playerWinner = reply[1];
			break;
		case 'O':
			gameGoing = false;
			winner = true;
			playerWinner = reply[1];
			break;
		case 'D':
			gameGoing = false;
			draw = true;
			break;
		case '0':
			break;
		}
	}
}










void TatetiClient::clearScreen(HANDLE hConsole){
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

void TatetiClient::CrearKeyboardBuffer(){
	while (_kbhit())
	{
		_getche();
	}
}