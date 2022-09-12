#ifndef LISTENER_H
#define LISTENER_H


#include "NetworkAPI.h"

#include <iostream>
#include <string.h>
#include <string>

#include "Types.h"
#include "HandlerRequest.h"

class Listener {
private:
    ServerData receivedData;
    NetworkAPI networkAPI;

    ClientData _processRequest(const std::string &buffer);
    bool _handleReceiveError(SOCKET &clientSocket, const int bytesReceived);
    bool _handleClientDisconnected(SOCKET &clientSocket, SOCKET &listening, const std::string &IPv4, const int port, const int bytesReceived);
    bool _initNetworkAPI(SOCKET& listening, SOCKET& clientSocket, const std::string IPv4, const unsigned int port);

public:
    void startListen(const std::string &IPv4 = "127.0.0.1", const unsigned int port = 54000);
};


#endif //LISTENER_H
