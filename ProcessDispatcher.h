#ifndef TEST_TEST_H
#define TEST_TEST_H

#include <stdio.h>

#include <signal.h>
#include <dirent.h>
#include <sys/types.h>

#include <string>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <vector>


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
    static Process getProccessInfo(const int PID);
    static bool isProcessExists(const int PID);
    static bool killProccess(const int PID);
};

#endif //TEST_TEST_H
