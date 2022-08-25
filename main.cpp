#include "Listener.h"

int main()
{
    Listener listener;
    // listener.startListen("127.0.0.1", 54011);


    std::string buffer("<action>getProccess <data>10\0");
    ReceivedData data;

    data.parseData(buffer);
    std::cout << data.data << std::endl;
    return 0;
}
