#ifndef HANDLER_REQUEST_H
#define HANDLER_REQUEST_H

#include <string>

#include "Types.h"
#include "ProcessDispatcher.h"


class HandlerRequest {
private:
    static void _request_GET_ONE(ClientData &answer, const ServerData &receivedData);
    static void _request_GET_ALL(ClientData &answer, const ServerData &receivedData);
    static void _request_KILL(ClientData &answer, const ServerData &receivedData);
    static void _request_STOP_SERVER(ClientData &answer, const ServerData &receivedData);

public:
    static ClientData handleRequest(const ServerData &receivedData);

};


#endif //HANDLER_REQUEST_H
