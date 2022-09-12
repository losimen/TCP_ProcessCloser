#include "HandlerRequest.h"


void HandlerRequest::_request_GET_ONE(ClientData &answer, const ServerData &receivedData) {
    Process process;

    try {
        process = ProcessDispatcher::getProcessInfo(std::stoi(receivedData.data));
    } catch(std::runtime_error err) {
        answer.data = TagWorker::createTag("info", std::string(err.what()));
        answer.status = STATUS_FAIL;
        return;
    }

    answer.data = TagWorker::createTag("PID", std::to_string(process.PID));
    answer.data += TagWorker::createTag("name", process.name);
    answer.status = STATUS_OK;
}


void HandlerRequest::_request_GET_ALL(ClientData &answer, const ServerData &receivedData) {
    ProcessList processList;
    try {
        processList = ProcessDispatcher::getListOfProcesses();
    } catch(std::runtime_error err) {
        answer.data = TagWorker::createTag("info", err.what());
        answer.status = STATUS_FAIL;
    }

    std::string listData;
    answer.status = STATUS_OK;
    for (auto process: processList) {
        std::string itemData;
        
        itemData += TagWorker::createTag("PID", std::to_string(process.PID));
        itemData += TagWorker::createTag("name", process.name);

        listData += TagWorker::createTag("item", itemData);
    }

    answer.data = TagWorker::createTag("pList", listData);
}


void HandlerRequest::_request_KILL(ClientData &answer, const ServerData &receivedData) {
    if (ProcessDispatcher::killProcess(std::stoi(receivedData.data))) {
        answer.status = STATUS_OK;
        answer.data = TagWorker::createTag("info", "Success");
    } else {
        answer.status = STATUS_FAIL;
        answer.data = TagWorker::createTag("info", "Process doesn't exist");
    }   
}


void HandlerRequest::_request_STOP_SERVER(ClientData &answer, const ServerData &receivedData) {
    answer.status = STATUS_HALT;
    answer.data = TagWorker::createTag("info", "Server is stopped");
}


ClientData HandlerRequest::handleRequest(const ServerData &receivedData) {
    ClientData answer;

    std::cout << "REQUEST: " << receivedData.action << " | DATA: " << receivedData.action << std::endl;

    if (receivedData.action == ACTION_GET_ONE)
        HandlerRequest::_request_GET_ONE(answer, receivedData);
    else if (receivedData.action == ACTION_GET_ALL)
        HandlerRequest::_request_GET_ALL(answer, receivedData);
    else if (receivedData.action == ACTION_KILL)
        HandlerRequest::_request_KILL(answer, receivedData);
    else if (receivedData.action == ACTION_STOP_SERVER)
        HandlerRequest::_request_STOP_SERVER(answer, receivedData);
    else {
        answer.status = STATUS_FAIL;
        answer.data = TagWorker::createTag("info", "Invalid operation");
    }

    std::cout << "RESPONCE: " << answer.serializeData() << std::endl;

    return answer;
}