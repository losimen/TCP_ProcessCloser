#include "Listener.h"

int main()
{
    Listener listener;
    // listener.startListen("127.0.0.1", 54002);

    ReceivedData receivedData;

    receivedData.parseData("<action>killProcess <data>gggg");
    std::cout << "ACTION: " << receivedData.action<< std::endl;
    std::cout << "DATA: " << receivedData.data  << std::endl;
 
    return 0;
}
