#include "NetworkApi.h"

#include <iostream>
#include <string>

#include "Types.h"
#include "ClientUI.h"


class ServerConnector {
private:
	NetworkAPI networkAPI;
	ServerData dataToSend_obj;

	bool _handleReceiveError(SOCKET& clientSocket, char* bufReceived, const int LENGTH_BUF);
	bool _handleSendError(SOCKET &clientSocket, const std::string &dataToSend);
	bool _handleUserAction();

	bool _establishConnection(SOCKET &clientSocket, const std::string &IPv4, const unsigned int port);

public:
	void startCommunication(const std::string &IPv4, const unsigned int port);

};
