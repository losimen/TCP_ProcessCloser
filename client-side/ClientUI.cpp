#include "ClientUI.h"

void ClientUI::_printUserMenu() {
    std::cout << "\n"
              << "---MAIN MENU---\n"
              << "1-> Get list of processes\n"
              << "2-> Get process by id\n"
              << "3-> Kill process\n"
              << "0-> Exit programm\n"
              << ">> ";
}


std::string ClientUI::_askUserPID() {
    std::string userRes;
    std::cout << "\n" 
              << "Enter PID: "; 

    std::getline(std::cin, userRes);

    return userRes;
}


DataToSend ClientUI::getUserAction() {
    DataToSend dataToSend;

    std::string userInputData;
    std::string userInputAction;

    ClientUI::_printUserMenu();
    std::getline(std::cin, userInputAction);

    if (userInputAction == "2" || userInputAction == "3")
        userInputData = ClientUI::_askUserPID();

    dataToSend.data = userInputData;
    dataToSend.action = userInputAction;

    return dataToSend;
}


void ClientUI::_request_A_GET_ONE(const std::string &buffer) {
    std::cout << "PID: " << TagWorker::getTagContent(buffer, "PID") << "\n"
                      << "Process name: " << TagWorker::getTagContent(buffer, "name") << "\n";
}


void ClientUI::_request_A_GET_ALL(const std::string &buffer) {
    std::vector<std::string> processList = TagWorker::getTagContentList(buffer, "pList", "item");

    for (auto process: processList)
        ClientUI::_request_A_GET_ONE(process);
}


void ClientUI::_request_A_KILL(const std::string &buffer) {
    std::cout << "Info: " << TagWorker::getTagContent(buffer, "info") << "\n";
}


void ClientUI::printServerAnswer(std::string buffer, const std::string &userAction) {
    std::cout << "\n---Server responce---\n";

    std::string status = TagWorker::getTagContent(buffer, "status");

    if (status == STATUS_OK) {
        if (userAction == ACTION_GET_ONE)
            ClientUI::_request_A_GET_ONE(buffer);
        else if (userAction == ACTION_GET_ALL)
            ClientUI::_request_A_GET_ALL(buffer);
        else if (userAction == ACTION_KILL)
            ClientUI::_request_A_KILL(buffer);

    } else {
        std::cout << "Server error: " << TagWorker::getTagContent(buffer, "info") << "\n";
    }

    std::cout << "--------\n";
}