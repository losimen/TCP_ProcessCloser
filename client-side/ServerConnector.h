#ifndef SERVER_CONNECTOR_H
#define SERVER_CONNECTOR_H

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#include "ClientTypes.h"
#include "ClientUI.h"


class ServerConnector {
private:
    static int _initClientSocket();
    static sockaddr_in _initServerAddress(const std::string &IPv4, const unsigned int port);
    static void _establishConnection(int &sock, sockaddr_in &hint);

public:
    static void connectToTheServer(const std::string &IPv4, const unsigned int port);

};


#endif //SERVER_CONNECTOR_H
