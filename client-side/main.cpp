#include "ServerConnector.h"


int main()
{
    ServerConnector serverConnector;
    serverConnector.startCommunication("127.0.0.1", 54000);

    return 0;
}