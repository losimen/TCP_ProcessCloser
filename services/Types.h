#ifndef SERVER_TYPES_H
#define SERVER_TYPES_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "TagWorker.h"

// action list:
#define ACTION_KILL "kill"
#define ACTION_GET_ONE "getProcess"
#define ACTION_GET_ALL "getProcessList"
#define ACTION_STOP_SERVER "stopServer"

// status list:
#define STATUS_OK "OK"
#define STATUS_FAIL "FAIL"


struct Process {
    int PID;
    std::string name;
};

typedef std::vector<Process> ProcessList;


struct ClientData {
    std::string status;
    std::string data;

    std::string serializeData();
};


struct ServerData {
    static const std::string F_DATA;
    static const std::string F_ACTION;

    std::string action;
    std::string data;

    void parseData(std::string buffer);
    std::string serializeData();
};


#endif //LISTENER_H