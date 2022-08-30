#include "ClientTypes.h"

std::string DataToSend::serializeData() {
    std::string result;

    if (DataToSend::action == "1")
        DataToSend::action = ACTION_GET_ALL;
    else if (DataToSend::action == "2")
        DataToSend::action = ACTION_GET_ONE;
    else if (DataToSend::action == "3")
        DataToSend::action = ACTION_KILL;
    else if (DataToSend::action == "0")
        DataToSend::action = "0";
    else 
        throw std::invalid_argument("Invalid argument");

    result = std::string("<action>") + DataToSend::action + std::string("</action>");
    result += std::string("<data>") + DataToSend::data + std::string("</data>") + std::string("\r\n");

    return result;
}

