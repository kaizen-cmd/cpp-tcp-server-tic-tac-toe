#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

#include "../boardGames/TicTacToe.h"
#include "server.h"

boardGames::TicTacToe* ticTacToeGame = new boardGames::TicTacToe();

// interact with anything on the server
// listener is outside the server
void handleClient(TCPServer *server, int clientSocket)
{

    std::pair<int, char>* opponentClient = &(server->clients.first.first == clientSocket ? server->clients.second : server->clients.first);
    std::pair<int, char>* currentClient = &(server->clients.first.first != clientSocket ? server->clients.second : server->clients.first);

    const char *response = "MSGWelcome to tic tac toe!";
    send(clientSocket, response, strlen(response), 0);

    char *buffer = new char[512];
    while (true)
    {
        ssize_t bytesRead = recv(clientSocket, buffer, 512, 0);

        if (bytesRead <= 0)
        {
            std::cout << "Client disconnected" << std::endl;
            break;
        }

        std::string bufferString = "MOV" + (std::string)buffer;
        
        // play the move
        int x = atoi(&bufferString[3]), y = atoi(&bufferString[5]);
        bufferString += currentClient->second;
        try {
            boardGames::TicTacToe::Result result = ticTacToeGame->play(x, y);
            bufferString += (char)(result + '0');
        }
        catch (const std::invalid_argument &ex) {
            std::cout << ex.what() << " Ip " << x << " " << y << std::endl;
        }
        send(opponentClient->first, bufferString.c_str(), 512, 0);
        send(currentClient->first, bufferString.c_str(), 512, 0);
        

        memset(buffer, '\0', 512);

    }

    close(clientSocket);
}

int main()
{    
    TCPServer server(8080, handleClient);
    server.startServer();
    return 0;
}