#ifndef HANDLER_REQUEST_H
#define HANDLER_REQUEST_H

#include <string>

#include "ServerTypes.h"

#ifdef __linux__ 
#include "LinuxAPI/ProcessDispatcher.h"

#elif _WIN32
#include "WindowsAPI/ProcessDispatcher.h"
#endif



class HandlerRequest {
private:
    static void _request_GET_ONE(Answer &answer, const ReceivedData &receivedData);
    static void _request_GET_ALL(Answer &answer, const ReceivedData &receivedData);
    static void _request_KILL(Answer &answer, const ReceivedData &receivedData);

public:
    static Answer handleRequest(const ReceivedData &receivedData);

};


#endif //HANDLER_REQUEST_H
