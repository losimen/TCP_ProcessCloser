#include "Listener.h"


void Listener::_initWinSock() {
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
		throw std::runtime_error(strerror(errno));
}


SOCKET Listener::_initListeningSocket(const std::string& IPv4, const unsigned int port) {
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
		throw std::runtime_error(strerror(errno));

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));
	return listening;
}


SOCKET Listener::_waitForConnection(SOCKET& listening) {
	std::cout << "Waiting for the connection " << std::endl;

	if (listen(listening, SOMAXCONN) == -1)
		throw std::runtime_error(strerror(errno));

	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];		
	char service[NI_MAXSERV];	

	ZeroMemory(host, NI_MAXHOST); 
	ZeroMemory(service, NI_MAXSERV);

	inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
	std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;

	closesocket(listening);
	return clientSocket;
}


Answer Listener::_processRequest(const std::string& buffer) {
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



void Listener::startListen(const std::string& IPv4, const unsigned int port) {
	const int LENGTH_BUF = 20000;

	std::cout << "Running server on address: " << IPv4 << ":" << port << std::endl;

	Listener::_initWinSock();
	SOCKET listening = Listener::_initListeningSocket(IPv4, port);
	SOCKET clientSocket = Listener::_waitForConnection(listening);
	char buf[LENGTH_BUF];

	while (true)
	{
		ZeroMemory(buf, LENGTH_BUF);
		int bytesReceived = recv(clientSocket, buf, LENGTH_BUF, 0);

		if (bytesReceived == SOCKET_ERROR) {
			closesocket(clientSocket);
			throw std::runtime_error(strerror(errno));
		}

		if (bytesReceived == 0) {
			std::cout << "Client disconected" << std::endl;
			closesocket(clientSocket);
			listening = Listener::_initListeningSocket(IPv4, port);
			clientSocket = Listener::_waitForConnection(listening);

			continue;
		}

		Answer answer = Listener::_processeRequest(std::string(buf, 0, bytesReceived));
		const std::string s_answer = answer.serializeData().c_str();

		ZeroMemory(buf, LENGTH_BUF);
		strcpy(buf, s_answer.c_str());

		send(clientSocket, buf, s_answer.length() + 1, 0);
	}

	WSACleanup();
}



