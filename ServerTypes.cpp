#include "ServerTypes.h"


const std::string ReceivedData::F_DATA = "<data>";
const std::string ReceivedData::F_ACTION  = "<action>";

bool invalidChar (char c) 
{  
    return !(c>=48 && c <122);   
} 

void stripUnicode(std::string & str) 
{ 
    str.erase(remove_if(str.begin(),str.end(), invalidChar), str.end());  
}

// <action>getProcess<data>1
void ReceivedData::parseData(std::string buffer) {
    stripUnicode(buffer);  
    std::cout << "Received data: " << buffer << " | LEN: " << buffer.length() << std::endl;

    const unsigned int symbolsToCut = (buffer.rfind(F_DATA)-buffer.find(F_ACTION)-F_ACTION.length());

    std::cout <<  ((buffer.find(F_ACTION) == std::string::npos) || (buffer.find(F_DATA) == std::string::npos)) << std::endl;

    if (buffer.find(F_DATA) == std::string::npos || buffer.find(F_ACTION) == std::string::npos)
        throw std::runtime_error("Invalid data format from client");
    
    ReceivedData::action = buffer.substr(8, symbolsToCut);
    ReceivedData::data = buffer.substr(buffer.find(F_DATA)+6);
}


void Answer::parse_A_GET_ONE(const int PID, const std::string &name) {
    

}


std::string Answer::serializeData() {
    std::string result; 

    result = std::string("<status>") + Answer::status;
    result += std::string("<data>") + Answer::data;

    return result;
}
