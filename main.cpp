#include <iostream>

#include "ProcessDispatcher.h"

int main () {
    int PID = 545354451;
 
    if (ProcessDispatcher::isProcessExists(PID)) {
        Process process = ProcessDispatcher::getProcessInfo(PID);
        std::cout << "PID: " << process.PID << std::endl;
        std::cout << "Name: " << process.name << std::endl;
        std::cout << "State: " << process.state << std::endl;
        std::cout << std::endl << std::endl;
    } else {
        std::cout << "Process doesn't exists" << std::endl;
    }
    
    PID = 1;
    if (ProcessDispatcher::isProcessExists(PID)) {
        Process process = ProcessDispatcher::getProcessInfo(PID);
        std::cout << "PID: " << process.PID << std::endl;
        std::cout << "Name: " << process.name << std::endl;
        std::cout << "State: " << process.state << std::endl;
        std::cout << std::endl << std::endl;
    } else {
        std::cout << "Process doesn't exists" << std::endl;
    }
    
    std::vector<Process> processes = ProcessDispatcher::getListOfProcesses();
    for (auto proces: processes)
    {
        std::cout << "PID: " << proces.PID << std::endl;
        std::cout << "Name: " << proces.name << std::endl;
        std::cout << "State: " << proces.state << std::endl;
        std::cout << std::endl << std::endl;
    }

    std::cout << ProcessDispatcher::killProcess(133443) << std::endl;

    return 0;
}
