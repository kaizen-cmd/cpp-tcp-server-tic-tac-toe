#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>
#include "../boardGames/TicTacToe.h"

const char *SERVER_IP = "0.0.0.0";
const int PORT = 8080;

void receiver(int sock, boardGames::TicTacToe* ticTacToeGame, bool* threadRunning) {
	int status;
	while(true) {
		char *buffer = new char[512];
		int bytes = recv(sock, buffer, 512, 0);
		std::string bufferString = buffer;
		std::string typ = bufferString.substr(0, 3);
		if(typ.compare("MSG") == 0) std::cout << buffer << std::endl;
		if(typ.compare("MOV") == 0) {
			bufferString = bufferString.substr(3, 5);
            int x = atoi(&bufferString[0]), y = atoi(&bufferString[2]);
			status = atoi(&bufferString[4]);
			char symbol = bufferString[3];
			ticTacToeGame->updateBoard(x, y, bufferString[3]);
			ticTacToeGame->displayBoard();
			if(status != boardGames::TicTacToe::Result::Continue) break;
		}
	}
	std::cout << "Game ended!" << std::endl;
	switch(status) {
		case boardGames::TicTacToe::Result::Player1Win:
			std::cout << "Player 1 won" << std::endl;
			break;
		case boardGames::TicTacToe::Result::Player2Win:
			std::cout << "Player 2 won" << std::endl;
			break;
		case boardGames::TicTacToe::Result::Tie:
			std::cout << "Tie!" << std::endl;
			break;
		default:
			break;
	}
	*threadRunning = false;
}

int main()
{	

	boardGames::TicTacToe* ticTacToeGame = new boardGames::TicTacToe();

	struct sockaddr_in serv_addr;

	int sock = socket(AF_INET, SOCK_STREAM, 0);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IP addresses from text to binary form
	inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr);

	// Connect to server
	int result = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	if(result != -1) {
		std::cout << "Connected to server. Type a message (type 'exit' to quit):" << std::endl;
	} else {
		close(sock);
		return 0;
	}

	bool val = true;
	bool* threadRunning = &val;
	std::thread recv_thread(receiver, sock, ticTacToeGame, threadRunning);
	recv_thread.detach();

	std::string message;

	while (true)
	{
		if(!val) break;
		std::getline(std::cin, message);
		send(sock, message.c_str(), message.length(), 0);
		if (message == "exit") break;
	}

	close(sock);

	return 0;
}
