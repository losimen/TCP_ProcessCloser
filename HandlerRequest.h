#ifndef HANDLER_REQUEST_H
#define HANDLER_REQUEST_H

#include <string>

#include "ServerTypes.h"
#include "ProcessDispatcher.h"


class HandlerRequest {
public:
    static Answer handleRequest(const ReceivedData &receivedData);

};


#endif //HANDLER_REQUEST_H
