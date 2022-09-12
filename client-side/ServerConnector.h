#include "NetworkApi.h"

#include <iostream>
#include <string>

#include "Types.h"
#include "ClientUI.h"


class ServerConnector {
private:
	NetworkAPI networkAPI;

	int _handleReceiveError(SOCKET& clientSocket, char* bufReceived, const int LENGTH_BUF);
	int _handleSendError(SOCKET &clientSocket, const std::string &dataToSend);

public:
	void startCommunication(const std::string &IPv4, const unsigned int port);

};
