#ifndef NETWORK_API_H
#define NETWORK_API_H

#include <iostream>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <WS2tcpip.h>
#include <string>

#pragma comment (lib, "ws2_32.lib")


class NetworkAPI {
public:
    static void initWinSock();
    static SOCKET initListeningSocket(const std::string& IPv4, const unsigned int port);
    static SOCKET waitForConnection(SOCKET& listening);
    static int receiveData(SOCKET clientSocket, char* buf, int buf_len);
};

#endif /*  NETWORK_API_H */
