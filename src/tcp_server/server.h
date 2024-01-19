#include <iostream>

class TCPServer
{

private:
    int port, serverSocket;
    void (*onClientConnected)(TCPServer *, int);

public:
    std::pair<std::pair<int, char>, std::pair<int, char>> clients;
    TCPServer(int port, void (*onClientConnected)(TCPServer *, int));
    ~TCPServer();
    void startServer();
};
