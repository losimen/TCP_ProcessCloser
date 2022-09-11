#ifndef LISTENER_H
#define LISTENER_H


#include "NetworkAPI.h"

#include <iostream>
#include <string.h>
#include <string>

#include "ServerTypes.h"
#include "HandlerRequest.h"

class Listener {
private:
    ReceivedData receivedData;
    Answer _processRequest(const std::string &buffer);
    
public:
    void startListen(const std::string &IPv4 = "127.0.0.1", const unsigned int port = 54000);
};


#endif //LISTENER_H
