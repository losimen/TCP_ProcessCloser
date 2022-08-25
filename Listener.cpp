#include "Listener.h"


int Listener::_initListeningSocket(const std::string &IPv4, const unsigned int port) {
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
        throw std::runtime_error(strerror(errno));

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, IPv4.c_str(), &hint.sin_addr);

    if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1)
        throw std::runtime_error(strerror(errno));

    return listening;
}


int Listener::_waitForConnection(int &listening) {
    std::cout << "Waiting for the connection " << std::endl;

    if (listen(listening, SOMAXCONN) == -1)
        throw std::runtime_error(strerror(errno));

    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
 
    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
 
    char host[NI_MAXHOST];     
    char service[NI_MAXSERV]; 
 
    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
 
    inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
    std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;

    close(listening);
    return clientSocket;
}


void Listener::startListen(const std::string &IPv4, const unsigned int port) {
    std::cout << "Running server on address: " << IPv4 << ":" << port << std::endl;

    int listening = Listener::_initListeningSocket(IPv4, port);
    int clientSocket = Listener::_waitForConnection(listening);
    char buf[4096];

    while (true)
    {
        memset(buf, 0, 4096);
        int bytesReceived = recv(clientSocket, buf, 4096, 0);

        if (bytesReceived == -1) {
            close(clientSocket);
            throw std::runtime_error(strerror(errno));
            break;
        }

        if (bytesReceived == 0) {
            std::cout << "Client disconected" << std::endl;
            close(clientSocket);
            listening = Listener::_initListeningSocket(IPv4, port);
            clientSocket = Listener::_waitForConnection(listening);

            continue;
        }

        std::cout << std::string(buf, 0, bytesReceived) << std::endl;
        send(clientSocket, buf, bytesReceived + 1, 0);
    }
}