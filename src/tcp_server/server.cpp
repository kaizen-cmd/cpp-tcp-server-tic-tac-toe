#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>
#include "server.h"


TCPServer::TCPServer(int port, void (*onClientConnected)(TCPServer *, int)) : port(port), onClientConnected(onClientConnected)
{
}
TCPServer::~TCPServer()
{
    std::cout << "Gracefully stopping the server" << std::endl;
    close(clients.first.first);
    close(clients.second.first);
    close(serverSocket);
}

void TCPServer::startServer()
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, 2);

    std::cout << "Server listening on port " << port << std::endl;

    while (true)
    {

        sockaddr_in clientAddress;
        socklen_t clientAddrLen = sizeof(clientAddress);

        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddrLen);

        if (!clients.first.first)
        {
            clients.first.first = clientSocket;
            clients.first.second = 'X';
        }
        else if (!clients.second.first)
        {
            clients.second.first = clientSocket;
            clients.second.second = 'O';
        }
        else
        {
            std::cout << "2 clients already connected" << std::endl;
            close(clientSocket);
            continue;
        }

        std::cout << "New connection from " << inet_ntoa(clientAddress.sin_addr) << ":" << ntohs(clientAddress.sin_port) << std::endl;

        std::thread clientThread(onClientConnected, this, clientSocket);
        clientThread.detach();
    }

    close(serverSocket);
}
