#include "Listener.h"

int main()
{
    Listener listener;
    listener.startListen("127.0.0.1", 54012);

    return 0;
}
