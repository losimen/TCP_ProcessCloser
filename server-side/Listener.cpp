#include "Listener.h"


ClientData Listener::_processRequest(const std::string &buffer) {
    ClientData answer;
    
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


bool Listener::_handleReceiveError(SOCKET &clientSocket, const int bytesReceived) {
    if (bytesReceived == -1) {
        Listener::networkAPI.closeSocket(clientSocket);
        return true;
    }

    return false;
}


bool Listener::_handleClientDisconnected(SOCKET &clientSocket, SOCKET &listening, const std::string &IPv4, const int port, const int bytesReceived) {
    if (bytesReceived == 0) {
        std::cout << "Client disconnected" << std::endl;
        Listener::networkAPI.closeSocket(clientSocket);
        listening = Listener::networkAPI.initListeningSocket(IPv4, port);
        clientSocket = Listener::networkAPI.waitForConnection(listening);

        return true;
    }
    
    return false;
}


void Listener::startListen(const std::string &IPv4, const unsigned int port) {
    const int LENGTH_BUF = 20000;
    SOCKET listening;
    SOCKET clientSocket;

    try {
        listening = Listener::networkAPI.initListeningSocket(IPv4, port);
        clientSocket = Listener::networkAPI.waitForConnection(listening);
    } catch (const std::runtime_error &err) {
        std::cout << strerror(errno) << std::endl;
        return;
    }

    char buf[LENGTH_BUF];

    while (true)
    {
        memset(buf, 0, LENGTH_BUF);
        int bytesReceived = Listener::networkAPI.receiveData(clientSocket, buf, LENGTH_BUF);

        if (Listener::_handleReceiveError(clientSocket, bytesReceived)) {
            std::cout << strerror(errno) << std::endl; 
            break;
        } 

        if (Listener::_handleClientDisconnected(clientSocket, listening, IPv4, port, bytesReceived)) {
            continue;
        }

        ClientData answer = Listener::_processRequest(std::string(buf, 0, bytesReceived));
        
        const std::string s_answer = answer.serializeData();
        Listener::networkAPI.sendData(clientSocket, s_answer.c_str(), s_answer.length());
    }
}
