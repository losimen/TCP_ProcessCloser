#ifndef LISTENER_H
#define LISTENER_H

#include <iostream>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <WS2tcpip.h>
#include <string>

#pragma comment (lib, "ws2_32.lib")

#include "ServerTypes.h"
#include "HandlerRequest.h"

class Listener {
    ReceivedData receivedData;
    void _initWinSock();
    SOCKET _initListeningSocket(const std::string& IPv4, const unsigned int port);
    SOCKET _waitForConnection(SOCKET& listening);
    Answer _processeRequest(const std::string& buffer);

public:
    void startListen(const std::string &IPv4 = "127.0.0.1", const unsigned int port = 5400);
};


#endif //LISTENER_H
