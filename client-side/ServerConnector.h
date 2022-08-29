#ifndef SERVER_CONNECTOR_H
#define SERVER_CONNECTOR_H

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>


class ServerConnector {
private:
    static int _initClientSocket();
    static sockaddr_in _initServerAddress(const std::string &IPv4, const unsigned int port);
    static void _establishConnection(int &sock, sockaddr_in &hint);

public:
    static void connectToTheServer(const std::string &IPv4 = "127.0.0.1", const unsigned int port = 5400);

};


#endif //SERVER_CONNECTOR_H
