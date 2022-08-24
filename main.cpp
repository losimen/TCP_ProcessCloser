#include <iostream>

#include "ProcessDispatcher.h"

int main () {
    // int PID = 545354451;
 
    // if (ProcessDispatcher::isProcessExists(PID)) {
    //     Process process = ProcessDispatcher::getProccessInfo(PID);
    //     std::cout << "PID: " << process.PID << std::endl;
    //     std::cout << "Name: " << process.name << std::endl;
    //     std::cout << "State: " << process.state << std::endl;
    //     std::cout << std::endl << std::endl;
    // } else {
    //     std::cout << "Process doesn't exists" << std::endl;
    // }
    
    // PID = 1;
    // if (ProcessDispatcher::isProcessExists(PID)) {
    //     Process process = ProcessDispatcher::getProccessInfo(PID);
    //     std::cout << "PID: " << process.PID << std::endl;
    //     std::cout << "Name: " << process.name << std::endl;
    //     std::cout << "State: " << process.state << std::endl;
    //     std::cout << std::endl << std::endl;
    // } else {
    //     std::cout << "Process doesn't exists" << std::endl;
    // }
    
    // std::vector<Process> processes = ProcessDispatcher::getListOfProcesses();
    // for (auto proces: processes)
    // {
    //     std::cout << "PID: " << proces.PID << std::endl;
    //     std::cout << "Name: " << proces.name << std::endl;
    //     std::cout << "State: " << proces.state << std::endl;
    //     std::cout << std::endl << std::endl;
    // }

    kill(29994, SIGTERM);
    kill(29995, SIGTERM);

    std::cout << "kill" << std::endl;

    return 0;
}
