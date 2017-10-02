#include "Game.h"



using namespace std;

Game::Game()
	:
	screen(GetStdHandle(STD_OUTPUT_HANDLE)),
	board(NULL),
	turn('X')
{}

Game::~Game(){
	delete[] board;
	delete[] lastMoveBoard;
}

bool Game::init(){
	char a[][3] = { {'7', '8', '9'},
					{'4', '5', '6'},
					{'1', '2', '3'}
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
	lastMoveBoard = board;
	gameGoing = true;
	playing = true;
	return true;
}

bool Game::play(){
	while (gameGoing){
		gameOver = false;
		clearScreen(screen);
		turn = playing ? 'X' : 'O';
		cout << "\n Turno de " << turn << endl << endl;

		for (size_t i = 0; i < 3; i++){
			switch (i)
			{
			case 1:
				cout << '\t' << "-----------" << endl << '\t';
				break;
			case 2:
				cout << '\t' << "-----------" << endl << '\t';
				break;
			default:
				cout << '\t';
				break;
			}
			for (size_t j = 0; j < 3; j++){
				switch (j)
				{
				case 0:
					cout << ' ' << board[i][j] << " |";
					break;
				case 1:
					cout << ' ' << board[i][j] << " |";
					break;
				default:
					cout << ' ' << board[i][j];
					break;
				}
				
			}
			cout << endl;
		}
		cout << endl;
		
		winer();

		//connectToServer();

		checkEnemyMove();
		lastMoveBoard = board;
		
		if (gameGoing && !gameOver){
			if (playing)
				playing = !playMoveX();
			else
				playing = playMoveO();
		}

	}

	return true;
}

void Game::checkEnemyMove(){
	if (lastMoveBoard != board){
		cout << " DIFERENTE";
		playing = true;
	}
}

bool Game::playMoveX(){
	int move = 0;

	cout << " Use de Numpad to chose a position: ";
	cin.clear();
	fflush(stdin);
	cin >> move;

	switch (move){
	case 1:
		if (board[2][0] != 'X' && board[2][0] != 'O'){
			board[2][0] = turn;
			return true;
		}
		else
			return false;
	case 2:
		if (board[2][1] != 'X' && board[2][1] != 'O'){
			board[2][1] = turn;
			return true;
		}
		else
			return false;
	case 3:
		if (board[2][2] != 'X' && board[2][2] != 'O'){
			board[2][2] = turn;
			return true;
		}
		else
			return false;
	case 4:
		if (board[1][0] != 'X' && board[1][0] != 'O'){
			board[1][0] = turn;
			return true;
		}
		else
			return false;
	case 5:
		if (board[1][1] != 'X' && board[1][1] != 'O'){
			board[1][1] = turn;
			return true;
		}
		else
			return false;
	case 6:
		if (board[1][2] != 'X' && board[1][2] != 'O'){
			board[1][2] = turn;
			return true;
		}
		else
			return false;
	case 7:
		if (board[0][0] != 'X' && board[0][0] != 'O'){
			board[0][0] = turn;
			return true;
		}
		else
			return false;
	case 8:
		if (board[0][1] != 'X' && board[0][1] != 'O'){
			board[0][1] = turn;
			return true;
		}
		else
			return false;
	case 9:
		if (board[0][2] != 'X' && board[0][2] != 'O'){
			board[0][2] = turn;
			return true;
		}
		else
			return false;
	}
	return false;
}

bool Game::playMoveO(){
	int move = 0;

	cout << " Use de Numpad to chose a position: ";
	cin.clear();
	fflush(stdin);
	cin >> move;

	switch (move){
	case 1:
		if (board[2][0] != 'X' && board[2][0] != 'O'){
			board[2][0] = turn;
			return true;
		}
		else
			return false;
	case 2:
		if (board[2][1] != 'X' && board[2][1] != 'O'){
			board[2][1] = turn;
			return true;
		}
		else
			return false;
	case 3:
		if (board[2][2] != 'X' && board[2][2] != 'O'){
			board[2][2] = turn;
			return true;
		}
		else
			return false;
	case 4:
		if (board[1][0] != 'X' && board[1][0] != 'O'){
			board[1][0] = turn;
			return true;
		}
		else
			return false;
	case 5:
		if (board[1][1] != 'X' && board[1][1] != 'O'){
			board[1][1] = turn;
			return true;
		}
		else
			return false;
	case 6:
		if (board[1][2] != 'X' && board[1][2] != 'O'){
			board[1][2] = turn;
			return true;
		}
		else
			return false;
	case 7:
		if (board[0][0] != 'X' && board[0][0] != 'O'){
			board[0][0] = turn;
			return true;
		}
		else
			return false;
	case 8:
		if (board[0][1] != 'X' && board[0][1] != 'O'){
			board[0][1] = turn;
			return true;
		}
		else
			return false;
	case 9:
		if (board[0][2] != 'X' && board[0][2] != 'O'){
			board[0][2] = turn;
			return true;
		}
		else
			return false;
	}
	return false;
}

bool Game::winer(){
	bool draw = false;
	int count = 0;
	for (size_t i = 0; i < 3; i++){
		for (size_t j = 0; j < 3; j++){
			if (board[i][j] == 'X' || board[i][j] == 'O'){
				count++;
			}
		}
	}

	if (count == 9){
		draw = true;
		gameOver = true;
		gameGoing = false;
	}

	gameGoing = (draw) ? false : true;
	if (gameGoing){

		for (size_t i = 0; i < 3; i++)
		{
			if (board[i][0] == board[i][1] && board[i][1] == board[i][2]){
				gameGoing = false;
				gameOver = true;
				cout << "\nPlayer " << board[i][0] << " has win!" << endl;
				break;
			}
		}

		for (size_t i = 0; i < 3; i++)
		{
			if (board[0][i] == board[1][i] && board[1][i] == board[2][i]){
				gameGoing = false;
				gameOver = true;
				cout << "\nPlayer " << board[0][i] << " has win!" << endl;
				break;
			}
		}

		if (board[0][0] == board[1][1] && board[1][1] == board[2][2]){
			gameGoing = false;
			gameOver = true;
			cout << "\nPlayer " << board[0][0] << " has win!" << endl;
		}
		else if (board[0][2] == board[1][1] && board[1][1] == board[2][0]){
			gameGoing = false;
			gameOver = true;
			cout << "\nPlayer " << board[0][2] << " has win!" << endl;
		}
	}
	else
		cout << "\nDraw!";

	if (!gameGoing){
		bool ok = false;
		while (!ok)
		{
			cout << "\nRestart? [y/n]: ";
			char temp;
			cin.clear();
			fflush(stdin);
			temp = cin.get();

			if (temp == 'y' || temp == 'Y'){
				init();
				ok = true;
				return true;
			}
			else if (temp == 'n' || temp == 'N'){
				ok = true;
				return true;
			}
		}
	}
	return false;
}

bool Game::connectToServer(){
	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];
	WSADATA wsa;

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

	//start communication
	while (playing)
	{
		printf("Enter message : ");
		gets_s(message);

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

		puts(buf);
		playing = false;
	}

	closesocket(s);
	WSACleanup();

	return true;
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