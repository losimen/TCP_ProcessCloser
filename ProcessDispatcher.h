#ifndef PROCESS_DISPATCHER_H
#define PROCESS_DISPATCHER_H


#include <string>
#include <string.h>
#include <iostream>
#include <vector>

#ifdef __linux__ 
#include <signal.h>
#include <dirent.h>
#include <sys/types.h>

#elif _WIN32
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>

#endif


struct Process {
    int PID;
    std::string name;
};


class ProcessDispatcher {   
#ifdef __linux__ 
private:
    static bool _charStartsWith(const char *a, const char *b);
    static std::string _parseProcessFileLine(std::string lineToParse);

    static const std::string PROC_DIR;
    static const std::string PROC_STAT_FILE;

#elif _WIN32
    static const std::string UNKOWN;
#endif

public:
    static std::vector<Process> getListOfProcesses();
    static Process getProcessInfo(const int PID);
    static bool isProcessExists(const int PID);
    static bool killProcess(const int PID);
};

#endif //PROCESS_DISPATCHER_H
