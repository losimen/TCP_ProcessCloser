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

// <action>getProccess<data>1
void ReceivedData::parseData(std::string buffer) {
    stripUnicode(buffer);
    
    std::cout << buffer << " " << buffer.length() << std::endl;

    const unsigned int symbolsToCut = (buffer.rfind(F_DATA)-buffer.find(F_ACTION)-F_ACTION.length());

    if (buffer.find(F_DATA) == std::string::npos || buffer.find(F_ACTION) == std::string::npos)
         std::runtime_error("Invalid data format from client");
    

    ReceivedData::action = buffer.substr(8, symbolsToCut);
    ReceivedData::data = buffer.substr(buffer.find(F_DATA)+6);

}
