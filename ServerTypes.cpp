#include "ServerTypes.h"


const std::string ReceivedData::F_DATA = "<data>";
const std::string ReceivedData::F_ACTION  = "<action>";


void ReceivedData::parseData(std::string buffer) {
    std::remove(buffer.begin(), buffer.end(), ' ');

    const unsigned int symbolsToCut = (buffer.rfind(F_DATA)-buffer.find(F_ACTION)-F_ACTION.length()-1);

    if (buffer.find(F_DATA) == std::string::npos || buffer.find(F_ACTION) == std::string::npos)
         std::runtime_error("Invalid data format from client");
    

    ReceivedData::action = buffer.substr(8, symbolsToCut);
    ReceivedData::data = buffer.substr(buffer.find(F_DATA)+7);
}
