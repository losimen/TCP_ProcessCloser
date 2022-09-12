#include "ServerConnector.h"


bool ServerConnector::_handleReceiveError(SOCKET &clientSocket, char *bufReceived, const int LENGTH_BUF) {
    int bytesReceived = networkAPI.receiveData(clientSocket, bufReceived, LENGTH_BUF);
    if (bytesReceived == -1) {
        std::cout << "There was an error getting response from server\r\n";
        return false;
    }

    return true;
}


bool ServerConnector::_handleSendError(SOCKET &clientSocket, const std::string &dataToSend) {
    int sendRes = networkAPI.sendData(clientSocket, dataToSend.c_str(), dataToSend.size());
    if (sendRes == -1) {
        std::cout << "There was an error sending data to the server\r\n";
        return false;
    }

    return true;
}


bool ServerConnector::_handleUserAction() {
    try {
        ServerConnector::dataToSend_obj = ClientUI::getUserAction();
        return true;
    }
    catch (std::invalid_argument err) {
        std::cout << "Invalid action" << std::endl;
        return false;
    }
}


bool ServerConnector::_initNetworkAPI(SOCKET &clientSocket, const std::string &IPv4, const unsigned int port) {
    try {
        clientSocket = networkAPI.initClientSocket();
        sockaddr_in hint = networkAPI.initServerAddress(IPv4, port);
        networkAPI.connectToTheServer(clientSocket, hint);

        return true;
    }
    catch (std::runtime_error err) {
        std::cout << err.what();

        return false;
    }
}


void ServerConnector::startCommunication(const std::string &IPv4, const unsigned int port) {
    const int LENGTH_BUF = 20000;
    SOCKET sock;

    if (!ServerConnector::_initNetworkAPI(sock, IPv4, port))
        return;

    char bufReceived[LENGTH_BUF];

    while (true) {
        std::string dataToSend_str;

        if (!ServerConnector::_handleUserAction())
            continue;

        dataToSend_str = ServerConnector::dataToSend_obj.serializeData();

        if (ServerConnector::dataToSend_obj.action == "0")
            break;

        if (!ServerConnector::_handleSendError(sock, dataToSend_str))
            continue;

        memset(bufReceived, 0, LENGTH_BUF);
        if (!ServerConnector::_handleReceiveError(sock, bufReceived, LENGTH_BUF))
            continue;

        ClientUI::printServerAnswer(bufReceived, ServerConnector::dataToSend_obj.action);
    }

    std::cout << "Bye-bye ^-^" << std::endl;
    networkAPI.closeSocket(sock);
}
