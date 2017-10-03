#include "TaTeTiServer.h"

TaTeTiServer::TaTeTiServer(){}

TaTeTiServer::~TaTeTiServer(){}

bool TaTeTiServer::init(){
	if (!server.init())
		return false;

	player1 = 'X';
	player1Id = "";
	player2 = 'O';
	player2Id = "";
	waitingForPlayers = true;
	playing = false;
	turnPlayer1 = true;

	char a[][3] = { { '7', '8', '9' },
					{ '4', '5', '6' },
					{ '1', '2', '3' }
	};
	board = new char*[3];
	for (size_t i = 0; i < 3; i++){
		board[i] = new char[3];
	}

	for (size_t i = 0; i < 3; i++){
		for (size_t j = 0; j < 3; j++){
			board[i][j] = a[i][j];
		}
	}

	return true;
}

bool TaTeTiServer::run(){
	printf("Waiting for players...");
	if (!waitingForPlayer())
		return false;

	if (!play())
		return false;

	return true;
}

bool TaTeTiServer::waitingForPlayer(){
	if (!server.waitingForData(data))
		return false;
	
	while (waitingForPlayers){
		if (data != ""){
			if (data == "1"){
				if (player1Id == ""){
					player1Id = server.getLastIp();
					if (!server.reply("1" + player1))
						return false;
				}
				else if (player2Id == ""){
					player2Id = server.getLastIp();
					if (!server.reply("1" + player2))
						return false;
					
				}
			}
		}

		data = "";
		
		if (player1Id != "" && player2Id != ""){
			waitingForPlayers = false;
			playing = true;
		}
	}
	
	return true;
}

bool TaTeTiServer::play(){
	while (playing)	{
		if (!server.waitingForData(data))
			return false;

		if (data != ""){
			if (data == "T"){
				if (turnPlayer1)
					server.reply("X");
				else
					server.reply("O");
			}
			else if (data == "B"){
				giveBoard();
			}
			else if (turnPlayer1 && player1Id == server.getLastIp() && data[0] == 'P'){
				makeAMove(data[1], player1);
				giveBoard();
				
			}
			else if (!turnPlayer1 && player2Id == server.getLastIp() && data[0] == 'P'){
				makeAMove(data[1], player2);
				giveBoard();
			}
			
			
			if (data == "1"){
				if (player1Id == ""){
					player1Id = server.getLastIp();
					if (!server.reply("1" + player1))
						return false;
				}
				else if (player2Id == ""){
					player2Id = server.getLastIp();
					if (!server.reply("1" + player2))
						return false;
				}
			}
		}
		data = "";
	}
	return true;
}

void TaTeTiServer::makeAMove(char place, char player){
	switch (place){
	case '1':
		if (board[2][0] != 'X' && board[2][0] != 'O'){
			board[2][0] = player;
			if (player == 'X')
				turnPlayer1 = false;
			else
				turnPlayer1 = true;
		}
	case '2':
		if (board[2][1] != 'X' && board[2][1] != 'O'){
			board[2][1] = player;
			if (player == 'X')
				turnPlayer1 = false;
			else
				turnPlayer1 = true;
		}
	case '3':
		if (board[2][2] != 'X' && board[2][2] != 'O'){
			board[2][2] = player;
			if (player == 'X')
				turnPlayer1 = false;
			else
				turnPlayer1 = true;
		}
	case '4':
		if (board[1][0] != 'X' && board[1][0] != 'O'){
			board[1][0] = player;
			if (player == 'X')
				turnPlayer1 = false;
			else
				turnPlayer1 = true;
		}
	case '5':
		if (board[1][1] != 'X' && board[1][1] != 'O'){
			board[1][1] = player;
			if (player == 'X')
				turnPlayer1 = false;
			else
				turnPlayer1 = true;
		}
	case '6':
		if (board[1][2] != 'X' && board[1][2] != 'O'){
			board[1][2] = player;
			if (player == 'X')
				turnPlayer1 = false;
			else
				turnPlayer1 = true;
		}
	case '7':
		if (board[0][0] != 'X' && board[0][0] != 'O'){
			board[0][0] = player;
			if (player == 'X')
				turnPlayer1 = false;
			else
				turnPlayer1 = true;
		}
	case '8':
		if (board[0][1] != 'X' && board[0][1] != 'O'){
			board[0][1] = player;
			if (player == 'X')
				turnPlayer1 = false;
			else
				turnPlayer1 = true;
		}
	case '9':
		if (board[0][2] != 'X' && board[0][2] != 'O'){
			board[0][2] = player;
			if (player == 'X')
				turnPlayer1 = false;
			else
				turnPlayer1 = true;
		}
	}
}

bool TaTeTiServer::giveBoard(){
	data[0] = 'B';
	for (size_t i = 0; i < 3; i++){
		for (size_t j = 0; j < 3; j++){
			data += board[i][j];
		}
	}
	if (!server.reply(data))
		return false;
	
	data = "";

	return true;
}