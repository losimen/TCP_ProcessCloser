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


Answer Listener::_processRequest(const std::string &buffer) {
    Answer answer;
    
    try {
        Listener::receivedData.parseData(buffer);
        answer = HandlerRequest::handleRequest(receivedData);
    }
    catch (std::runtime_error err) {
        std::cerr << "ERROR: " << err.what() << std::endl;

        answer.status = STATUS_FAIL;
        answer.data = err.what();
    }

    return answer;
}


void Listener::startListen(const std::string &IPv4, const unsigned int port) {
    const int LENGTH_BUF = 20000;

    std::cout << "Running server on address: " << IPv4 << ":" << port << std::endl;

    int listening = Listener::_initListeningSocket(IPv4, port);
    int clientSocket = Listener::_waitForConnection(listening);
    char buf[LENGTH_BUF];

    while (true)
    {
        memset(buf, 0, LENGTH_BUF);
        int bytesReceived = recv(clientSocket, buf, LENGTH_BUF, 0);

        if (bytesReceived == -1) {
            close(clientSocket);
            throw std::runtime_error(strerror(errno));
            
            break;
        }

        if (bytesReceived == 0) {
            std::cout << "Client disconnected" << std::endl;
            close(clientSocket);
            listening = Listener::_initListeningSocket(IPv4, port);
            clientSocket = Listener::_waitForConnection(listening);

            continue;
        }

        Answer answer = Listener::_processRequest(std::string(buf, 0, bytesReceived));
        const std::string s_answer = answer.serializeData().c_str();

        memset(buf, 0, LENGTH_BUF);
        strcpy(buf, s_answer.c_str());

        send(clientSocket, buf, s_answer.length() + 1, 0);
    }
}
