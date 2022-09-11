#include "Listener.h"


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

    SOCKET listening = NetworkAPI::initListeningSocket(IPv4, port);
    SOCKET clientSocket = NetworkAPI::waitForConnection(listening);
    char buf[LENGTH_BUF];

    while (true)
    {
        memset(buf, 0, LENGTH_BUF);
        int bytesReceived = NetworkAPI::receiveData(clientSocket, buf, LENGTH_BUF);

        if (bytesReceived == -1) {
            close(clientSocket);
            throw std::runtime_error(strerror(errno));
            
            break;
        }

        if (bytesReceived == 0) {
            std::cout << "Client disconnected" << std::endl;
            close(clientSocket);
            listening = NetworkAPI::initListeningSocket(IPv4, port);
            clientSocket = NetworkAPI::waitForConnection(listening);

            continue;
        }

        Answer answer = Listener::_processRequest(std::string(buf, 0, bytesReceived));
        const std::string s_answer = answer.serializeData().c_str();

        memset(buf, 0, LENGTH_BUF);
        strcpy(buf, s_answer.c_str());

        send(clientSocket, buf, s_answer.length() + 1, 0);
    }
}
