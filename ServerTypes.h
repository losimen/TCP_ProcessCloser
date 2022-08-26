#ifndef SERVER_TYPES_H
#define SERVER_TYPES_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>


// action list:
#define A_KILL "kill"
#define A_GET_ONE "getProcess"
#define A_GET_ALL "getProcessList"

// stauts list:
#define S_OK "OK"
#define S_FAIL "FAIL"


struct Process {
    int PID;
    std::string name;
};


struct Answer {
    std::string status;
    std::string data;

    void parse_A_GET_ONE(const int PID, const std::string &name);

    std::string serializeData();
};


struct ReceivedData {
    static const std::string F_DATA;
    static const std::string F_ACTION;

    std::string action;
    std::string data;

    void parseData(std::string buffer);
};

#endif //LISTENER_H