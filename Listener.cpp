#include "Listener.h"


int Listener::_initListeningSocket(const std::string &IPv4, const unsigned int port) {
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1) {
        std::cerr << "Can't create a socket! Quitting" << std::endl;
        return -1;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, IPv4.c_str(), &hint.sin_addr);

    bind(listening, (sockaddr*)&hint, sizeof(hint));
    return listening;
}


int Listener::_waitForConnection(int &listening) {
    std::cout << "Waiting for the connection " << std::endl;
    listen(listening, SOMAXCONN);

    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
 
    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
 
    char host[NI_MAXHOST];      // Client's remote name
    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
 
    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
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
            std::cerr << "Error in recv(). Quitting" << std::endl;
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