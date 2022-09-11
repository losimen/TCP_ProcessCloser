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


bool Listener::_handleReceiveError(const SOCKET clientSocket, const int bytesReceived) {
    if (bytesReceived == -1) {
        close(clientSocket);
        return true;
    }

    return false;
}


bool Listener::_handleClientDisconnected(SOCKET &clientSocket, SOCKET &listening, const std::string &IPv4, const int port, const int bytesReceived) {
    if (bytesReceived == 0) {
        std::cout << "Client disconnected" << std::endl;
        close(clientSocket);
        listening = NetworkAPI::initListeningSocket(IPv4, port);
        clientSocket = NetworkAPI::waitForConnection(listening);

        return true;
    }
    
    return false;
}


void Listener::startListen(const std::string &IPv4, const unsigned int port) {
    const int LENGTH_BUF = 20000;
    SOCKET listening;
    SOCKET clientSocket;

    try {
        listening = NetworkAPI::initListeningSocket(IPv4, port);
        clientSocket = NetworkAPI::waitForConnection(listening);
    } catch (const std::runtime_error &err) {
        std::cout << strerror(errno) << std::endl;
        return;
    }

    char buf[LENGTH_BUF];

    while (true)
    {
        memset(buf, 0, LENGTH_BUF);
        int bytesReceived = NetworkAPI::receiveData(clientSocket, buf, LENGTH_BUF);

        if (Listener::_handleReceiveError(clientSocket, bytesReceived)) {
            std::cout << strerror(errno) << std::endl; 
            break;
        } 

        if (Listener::_handleClientDisconnected(clientSocket, listening, IPv4, port, bytesReceived)) {
            continue;
        }

        Answer answer = Listener::_processRequest(std::string(buf, 0, bytesReceived));
        
        const std::string s_answer = answer.serializeData();
        NetworkAPI::sendData(clientSocket, s_answer.c_str(), s_answer.length());
    }
}
