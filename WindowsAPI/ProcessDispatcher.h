#ifndef PROCESS_DISPATCHER_H
#define PROCESS_DISPATCHER_H


#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>

#include "../ServerTypes.h"


class ProcessDispatcher {   
    static const std::string UNKOWN;

public:
    static ProcessList getListOfProcesses();
    static Process getProcessInfo(const int PID);
    static bool isProcessExists(const int PID);
    static bool killProcess(const int PID);
};

#endif //PROCESS_DISPATCHER_H
