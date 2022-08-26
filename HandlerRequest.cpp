#include "HandlerRequest.h"


Answer HandlerRequest::handleRequest(const ReceivedData &receivedData) {
    if (receivedData.action == A_GET_ONE)
    {
        Process process = ProcessDispatcher::getProcessInfo(std::stoi(receivedData.data));
        std::cout << process.PID << " " << process.name << std::endl;
    }
    else if (receivedData.action == A_KILL)
        ProcessDispatcher::killProcess(std::stoi(receivedData.data));
    else {
        std::cout << "unkown action " << std::endl;
    }

    return Answer();
}