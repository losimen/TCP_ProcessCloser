#include "Types.h"


const std::string ServerData::F_DATA = "data";
const std::string ServerData::F_ACTION = "action";


std::string ServerData::serializeData() {
    std::string result;

    if (ServerData::action == "1")
        ServerData::action = ACTION_GET_ALL;
    else if (ServerData::action == "2")
        ServerData::action = ACTION_GET_ONE;
    else if (ServerData::action == "3")
        ServerData::action = ACTION_KILL;
    else if (ServerData::action == "0")
        ServerData::action = "0";
    else
        throw std::invalid_argument("Invalid argument");

    result = std::string("<action>") + ServerData::action + std::string("</action>");
    result += std::string("<data>") + ServerData::data + std::string("</data>") + std::string("\r\n");

    return result;
}


void ServerData::parseData(std::string buffer) {
    try {
        ServerData::action = TagWorker::getTagContent(buffer, "action");
        ServerData::data = TagWorker::getTagContent(buffer, "data");
    }
    catch (std::runtime_error err) {
        throw std::runtime_error("Invalid data format from client");
    }
}


std::string ClientData::serializeData() {
    std::string result;

    result = std::string("<status>") + ClientData::status + std::string("</status>");
    result += std::string("<data>") + ClientData::data + std::string("</data>") + std::string("\r\n");

    return result;
}
