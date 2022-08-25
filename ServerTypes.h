#ifndef SERVER_TYPES_H
#define SERVER_TYPES_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#define A_KILL "kill"
#define A_GET "getProcess"


struct Process {
    int PID;
    std::string name;
};


enum StatusCode {
    OK,
    FAIL
};


struct Answer {
    StatusCode statusCode;
    std::string data;
};


struct ReceivedData {
    static const std::string F_DATA;
    static const std::string F_ACTION;

    std::string action;
    std::string data;

    void parseData(std::string buffer);
};

#endif //LISTENER_H