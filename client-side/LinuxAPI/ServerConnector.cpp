#include "ServerConnector.h"


int ServerConnector::_initClientSocket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        throw std::runtime_error(strerror(errno));
    
    return sock;
}

sockaddr_in ServerConnector::_initServerAddress(const std::string &IPv4, const unsigned int port) {
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, IPv4.c_str(), &hint.sin_addr);

    return hint;
}


void ServerConnector::_connectToTheServer(int &sock, sockaddr_in &hint) {
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));

    if (connectRes == -1)
        throw std::runtime_error("Connection refused\n");
}


void ServerConnector::establishConnection(const std::string &IPv4, const unsigned int port) {
    // TODO: make it dynamic
    const int LENGTH_BUF = 20000;
    int sock;

    try {
        sock = ServerConnector::_initClientSocket();
        sockaddr_in hint = ServerConnector::_initServerAddress(IPv4, port);
        ServerConnector::_connectToTheServer(sock, hint);
    }
    catch (std::runtime_error err) {
        std::cout << err.what();
        return;
    }

    char bufReceived[LENGTH_BUF];
    std::string dataToSend_str;
    DataToSend dataToSend_obj;

    while (true) {
        try {
            dataToSend_obj = ClientUI::getUserAction();
            dataToSend_str = dataToSend_obj.serializeData();

        } catch (std::runtime_error err) {
            std::cout << err.what() << " | Try again" << std::endl;
            continue;
        } catch (std::invalid_argument err) {
            std::cout << err.what() << " | Try again" << std::endl;
            continue;
        }

        if (dataToSend_obj.action == "0")
            break;

        int sendRes = send(sock, dataToSend_str.c_str(), dataToSend_str.size() + 1, 0);

        if (sendRes == -1) {
            std::cout << "Could not send to server! Whoops!\r\n";
            continue;
        }

        memset(bufReceived, 0, LENGTH_BUF);
        int bytesReceived = recv(sock, bufReceived, LENGTH_BUF, 0);

        if (bytesReceived == -1)
            std::cout << "There was an error getting response from server\r\n";
        else {
            try {
                ClientUI::printServerAnswer(bufReceived, dataToSend_obj.action);
            } catch(std::runtime_error err) {
                std::cout << err.what() << std::endl;
            }
        }
    }

    std::cout << "Bye-bye ^-^" << std::endl;
    close(sock);
}
