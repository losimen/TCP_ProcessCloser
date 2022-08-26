#include "ServerTypes.h"


const std::string ReceivedData::F_DATA = "data";
const std::string ReceivedData::F_ACTION  = "action";


// <action>getProcess</action><data>1</data>
void ReceivedData::parseData(std::string buffer) {    
    try {
        ReceivedData::action = TagWorker::getTagContent(buffer, "action");     
        ReceivedData::data = TagWorker::getTagContent(buffer, "data");
    }
    catch (std::runtime_error err) {
        throw std::runtime_error("Invalid data format from client");
    }
}


std::string Answer::serializeData() {
    std::string result; 

    result = std::string("<status>") + Answer::status + std::string("</status>");
    result += std::string("<data>") + Answer::data + std::string("</data>");

    return result;
}
