#include "ClientUI.h"


const int ClientUI::MAX_ACTION_NUM = 3;


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


ServerData ClientUI::getUserAction() {
    ServerData dataToSend;

    std::string userInputData;
    std::string userInputAction;

    ClientUI::_printUserMenu();
    std::getline(std::cin, userInputAction);

    int userInputAction_num;
    userInputAction_num = std::stoi(userInputAction);
    if (userInputAction_num >= MAX_ACTION_NUM) {
        throw std::invalid_argument("");
    }

    if (userInputAction == "2" || userInputAction == "3")
        userInputData = ClientUI::_askUserPID();

    dataToSend.data = userInputData;
    dataToSend.action = userInputAction;

    return dataToSend;
}


void ClientUI::_request_A_GET_ONE(const std::string &buffer) {
    const char separator    = ' ';
    const int width = 8;

    std::cout << "PID: " << TagWorker::getTagContent(buffer, "PID") << "\n"
              << "Process name: " << TagWorker::getTagContent(buffer, "name") << "\n";
}


void ClientUI::_request_A_GET_ALL(const std::string &buffer) {
    std::vector<std::string> processList = TagWorker::getTagContentList(buffer, "pList", "item");
    const char separator = ' ';
    const int widthName = 20;
    const int widthNum = 10;

    std::cout << std::left << std::setw(widthNum) << std::setfill(separator) << "PID";
    std::cout << std::left << std::setw(widthName) << std::setfill(separator) << "Process name ";
    std::cout << std::endl;

    for (auto process: processList){
        std::cout << std::left << std::setw(widthNum) << std::setfill(separator) << TagWorker::getTagContent(process, "PID");
        std::cout << std::left << std::setw(widthName) << std::setfill(separator) << TagWorker::getTagContent(process, "name");
        std::cout << std::endl;
    }
        
}


void ClientUI::_request_A_KILL(const std::string &buffer) {
    std::cout << "Info: " << TagWorker::getTagContent(buffer, "info") << "\n";
}


void ClientUI::printServerAnswer(std::string buffer, const std::string &userAction) {
    std::cout << "\n---Server responce---\n";
    std::string status;

    try {
        status  = TagWorker::getTagContent(buffer, "status");
    }
    catch (std::runtime_error& err) {
        std::cout << "Invalid server receive format" << std::endl;
    }

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