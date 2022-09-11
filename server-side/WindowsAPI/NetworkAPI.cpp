#include "NetworkAPI.h"


void NetworkAPI::initWinSock() {
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
		throw std::runtime_error(strerror(errno));
}


SOCKET NetworkAPI::waitForConnection(SOCKET& listening) {
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


SOCKET NetworkAPI::initListeningSocket(const std::string& IPv4, const unsigned int port) {
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


int NetworkAPI::receiveData(SOCKET clientSocket, char* buf, int buf_len) {
	return recv(clientSocket, buf, buf_len, 0);
}
