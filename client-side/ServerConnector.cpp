#include "ServerConnector.h"


int ServerConnector::_handleReceiveError(SOCKET &clientSocket, char *bufReceived, const int LENGTH_BUF) {
    int bytesReceived = networkAPI.receiveData(clientSocket, bufReceived, LENGTH_BUF);
    if (bytesReceived == -1) {
        std::cout << "There was an error getting response from server\r\n";
        return false;
    }

    return true;
}


int ServerConnector::_handleSendError(SOCKET &clientSocket, const std::string &dataToSend) {
    int sendRes = networkAPI.sendData(clientSocket, dataToSend.c_str(), dataToSend.size());
    if (sendRes == -1) {
        std::cout << "Could not send to server! Whoops!\r\n";
        return false;
    }

    return true;
}


void ServerConnector::startCommunication(const std::string &IPv4, const unsigned int port) {
    const int LENGTH_BUF = 20000;
    SOCKET sock;

    try {
        sock = networkAPI.initClientSocket();
        sockaddr_in hint = networkAPI.initServerAddress(IPv4, port);
        networkAPI.connectToTheServer(sock, hint);
    }
    catch (std::runtime_error err) {
        std::cout << err.what();
        return;
    }

    char bufReceived[LENGTH_BUF];
    std::string dataToSend_str;
    ServerData dataToSend_obj;

    while (true) {
        dataToSend_obj = ClientUI::getUserAction();
        dataToSend_str = dataToSend_obj.serializeData();

        if (dataToSend_obj.action == "0")
            break;

        ServerConnector::_handleSendError(sock, dataToSend_str);

        memset(bufReceived, 0, LENGTH_BUF);
        ServerConnector::_handleReceiveError(sock, bufReceived, LENGTH_BUF);

        ClientUI::printServerAnswer(bufReceived, dataToSend_obj.action);
    }

    std::cout << "Bye-bye ^-^" << std::endl;
    networkAPI.closeSocket(sock);
}
