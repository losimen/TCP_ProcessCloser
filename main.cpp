#ifdef __linux__ 
#include "LinuxAPI/Listener.h"

#elif _WIN32
#include "WindowsAPI/Listener.h"
#endif

int main()
{
    Listener listener;
    listener.startListen("127.0.0.1", 54026);

    return 0;
}
