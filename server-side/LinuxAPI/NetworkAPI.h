#ifndef  NETWORK_API_H
#define NETWORK_API_H


#include <iostream>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

typedef int SOCKET;

class NetworkAPI {
public:
    static SOCKET initListeningSocket(const std::string &IPv4, const unsigned int port);
    static SOCKET waitForConnection(SOCKET &listening);
    static int receiveData(SOCKET clientSocket, char *buf, int buf_len);
    static void sendData(SOCKET clientSocket, const char *s_answer, const int s_answer_len);
};

#endif /*  NETWORK_API_H */
