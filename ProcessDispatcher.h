#ifndef PROCESS_DISPATCHER_H
#define PROCESS_DISPATCHER_H


#include <string>
#include <string.h>
#include <iostream>
#include <vector>

#include <signal.h>
#include <dirent.h>
#include <sys/types.h>


struct Process {
    int PID;
    std::string name;
    std::string state;
};


class ProcessDispatcher {   
private:
    static bool charStartsWith(const char *a, const char *b);
    static std::string parseProcessFileLine(std::string lineToParse);

    static const std::string PROC_DIR;
    static const std::string PROC_STAT_FILE;

public:
    static std::vector<Process> getListOfProcesses();
    static Process getProcessInfo(const int PID);
    static bool isProcessExists(const int PID);
    static bool killProcess(const int PID);
};

#endif //PROCESS_DISPATCHER_H
