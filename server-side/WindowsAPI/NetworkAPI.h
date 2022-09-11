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
private:
    void _initWinSock();

public:
    NetworkAPI();

    SOCKET initListeningSocket(const std::string& IPv4, const unsigned int port);
    SOCKET waitForConnection(SOCKET& listening);
    int receiveData(SOCKET clientSocket, char* buf, int buf_len);
    void sendData(SOCKET clientSocket, const char* s_answer, const int s_answer_len);
    void closeSocket(SOCKET &socket);
};

#endif /*  NETWORK_API_H */
