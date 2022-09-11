#ifndef LISTENER_H
#define LISTENER_H

#include <iostream>
#include <string.h>
#include <string>

#include "ServerTypes.h"
#include "HandlerRequest.h"
#include "NetworkAPI.h"

class Listener {
private:
    ReceivedData receivedData;

    Answer _processRequest(const std::string &buffer);
    bool _handleReceiveError(const SOCKET clientSocket, const int bytesReceived);
    bool _handleClientDisconnected(SOCKET &clientSocket, SOCKET &listening, const std::string &IPv4, const int port, const int bytesReceived);
    
public:
    void startListen(const std::string &IPv4 = "127.0.0.1", const unsigned int port = 54000);
};


#endif //LISTENER_H
