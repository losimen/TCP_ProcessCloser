#include "ProcessDispatcher.h"

const std::string ProcessDispatcher::UNKOWN = "<unknown>";


ProcessList ProcessDispatcher::getListOfProcesses() {
    ProcessList listOfProcesses;

    DWORD processesPID[1024], amountOfBytes, amountOfProcesses;
    unsigned int i;

    if (!EnumProcesses(processesPID, sizeof(processesPID), &amountOfBytes))
        throw std::runtime_error("Cannot get request list");

    amountOfProcesses = amountOfBytes / sizeof(DWORD);

    for (i = 0; i < amountOfProcesses; i++)
    {
        if (processesPID[i] != 0)
        {
            Process process = ProcessDispatcher::getProcessInfo(processesPID[i]);

            if (process.name == UNKOWN)
                continue;

            listOfProcesses.push_back(process);
        }

    }

    return listOfProcesses;
}


Process ProcessDispatcher::getProcessInfo(const int PID) {
    Process process;
    TCHAR processName[MAX_PATH] = TEXT("<unknown>");
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, PID);

    if (hProcess != nullptr) {
        HMODULE hMod;
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
            GetModuleBaseName(hProcess, hMod, processName, sizeof(processName) / sizeof(TCHAR));
    }

    process.name = processName;
    process.PID = PID;

    CloseHandle(hProcess);
    return process;
}


bool ProcessDispatcher::isProcessExists(const int PID) {
    return ProcessDispatcher::getProcessInfo(PID).name != UNKOWN;
}


bool ProcessDispatcher::killProcess(const int PID) {
    if (!ProcessDispatcher::isProcessExists(PID))
        return false;

    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, false, PID);
    TerminateProcess(hProcess, 1);
    CloseHandle(hProcess);
    return true;
}
