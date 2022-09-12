#include "NetworkAPI.h"


int NetworkAPI::initListeningSocket(const std::string &IPv4, const unsigned int port) {
    int listening = socket(AF_INET, SOCK_STREAM, 0);

    if (listening == -1)
        throw std::runtime_error(strerror(errno));

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, IPv4.c_str(), &hint.sin_addr);

    if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1)
        throw std::runtime_error(strerror(errno));

    std::cout << "Running server on address: " << IPv4 << ":" << port << std::endl;
    
    return listening;
}


SOCKET NetworkAPI::initClientSocket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        throw std::runtime_error(strerror(errno));
    
    return sock;
}


sockaddr_in NetworkAPI::initServerAddress(const std::string& IPv4, const unsigned int port) {
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, IPv4.c_str(), &hint.sin_addr);

    return hint;
}


void NetworkAPI::connectToTheServer(SOCKET& sock, sockaddr_in& hint) {
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));

    if (connectRes == -1)
        throw std::runtime_error("Connection refused\n");

}


int NetworkAPI::waitForConnection(SOCKET &listening) {
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


int NetworkAPI::receiveData(SOCKET clientSocket, char *buf, int buf_len) {
    return recv(clientSocket, buf, buf_len, 0);
}


int NetworkAPI::sendData(SOCKET clientSocket, const char *s_answer, const int s_answer_len) {
    return send(clientSocket, s_answer, s_answer_len + 1, 0);
}


void NetworkAPI::closeSocket(SOCKET& socket) {
    close(socket);
}