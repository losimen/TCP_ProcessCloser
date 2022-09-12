#include "Types.h"


const std::string ServerData::F_DATA = "data";
const std::string ServerData::F_ACTION = "action";

std::map<int, std::string> actionsID{
    {0, "0"},
    {1, ACTION_GET_ALL},
    {2, ACTION_GET_ONE},
    {3, ACTION_KILL},
    {4, ACTION_STOP_SERVER}
};


std::string ServerData::serializeData() {
    std::string result;

    int action_num = std::stoi(ServerData::action);
    if (actionsID.find(action_num) == actionsID.end())
        throw std::invalid_argument("invalid argument");
    ServerData::action = actionsID[action_num];

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
