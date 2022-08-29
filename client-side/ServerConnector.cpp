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


void ServerConnector::_establishConnection(int &sock, sockaddr_in &hint) {
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));

    if (connectRes == -1)
        throw std::runtime_error("Connection refused");
}


void ServerConnector::connectToTheServer(const std::string &IPv4, const unsigned int port) {
    // TODO: make it dynamic
    const int LENGTH_BUF = 4096;

    int sock = ServerConnector::_initClientSocket();
    sockaddr_in hint = ServerConnector::_initServerAddress(IPv4, port);
    ServerConnector::_establishConnection(sock, hint);

    char buf[LENGTH_BUF];
    std::string userInput;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, userInput);

        if (userInput == "0")
            break;
        
        int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
        if (sendRes == -1)
        {
            std::cout << "Could not send to server! Whoops!\r\n";
            continue;
        }

        //		Wait for response
        memset(buf, 0, LENGTH_BUF);
        int bytesReceived = recv(sock, buf, LENGTH_BUF, 0);
        if (bytesReceived == -1)
        {
            std::cout << "There was an error getting response from server\r\n";
        }
        else
        {
            //		Display response
            std::cout << "SERVER> " << std::string(buf, bytesReceived) << "\r\n";
        }
    }

    //	Close the socket
    close(sock);
}

