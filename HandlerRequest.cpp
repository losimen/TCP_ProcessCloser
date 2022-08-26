#include "HandlerRequest.h"


Answer HandlerRequest::handleRequest(const ReceivedData &receivedData) {
    Answer answer;

    if (receivedData.action == A_GET_ONE) {
        Process process;
        try {
            process = ProcessDispatcher::getProcessInfo(std::stoi(receivedData.data));
        } catch(std::runtime_error err) {
            answer.data = TagWorker::createTag("info", err.what());
            answer.status = S_FAIL;

            return answer;
        }

        answer.data = TagWorker::createTag("PID", std::to_string(process.PID));
        answer.data += TagWorker::createTag("name", process.name);
        answer.status = S_OK;
    }
    else if (receivedData.action == A_KILL) {
        ProcessDispatcher::killProcess(std::stoi(receivedData.data));
    }
    else {
        std::cout << "unkown action " << std::endl;
    }

    return answer;
}