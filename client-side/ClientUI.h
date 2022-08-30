#ifndef CLIENT_UI_H
#define CLIENT_UI_H

#include <iostream>

#include "ClientTypes.h"
#include "TagWorker.h"


class ClientUI {
private:
    static void _printUserMenu();
    static std::string _askUserPID();

    static void _request_A_GET_ONE(const std::string &buffer);
    static void _request_A_GET_ALL(const std::string &buffer);
    static void _request_A_KILL(const std::string &buffer);


public:
    static DataToSend getUserAction();
    static void printServerAnswer(std::string buffer, const std::string &userAction);

};


#endif //CLIENT_UI_H
