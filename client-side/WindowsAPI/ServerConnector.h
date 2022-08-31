#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "ClientTypes.h"
#include "ClientUI.h"


class ServerConnector {
private:
	static void _initWinSock();
	static SOCKET _initClientSocket();
	static sockaddr_in _initServerAddress(const std::string &IPv4, const unsigned int port);
	static void _connectToTheServer(SOCKET &sock, sockaddr_in &hint);

public:
	static void establishConnection(const std::string &IPv4, const unsigned int port);

};