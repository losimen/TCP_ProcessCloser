#ifndef CLIENT_TYPES_H
#define CLIENT_TYPES_H

#include <string>
#include "TagWorker.h"

// action list:
#define ACTION_KILL "kill"
#define ACTION_GET_ONE "getProcess"
#define ACTION_GET_ALL "getProcessList"

// stauts list:
#define STATUS_OK "OK"
#define STATUS_FAIL "FAIL"


struct DataToSend {
    std::string action;
    std::string data;

    std::string serializeData();
};

#endif //CLIENT_TYPES_H
