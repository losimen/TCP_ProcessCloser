#ifndef LISTENER_H
#define LISTENER_H

#include <iostream>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "../ServerTypes.h"
#include "../HandlerRequest.h"

class Listener {
private:
    ReceivedData receivedData;
    int _initListeningSocket(const std::string &IPv4, const unsigned int port);
    int _waitForConnection(int &listening);
    Answer _processeRequest(const std::string &buffer);
    
public:
    void startListen(const std::string &IPv4 = "127.0.0.1", const unsigned int port = 5400);
};


#endif //LISTENER_H
