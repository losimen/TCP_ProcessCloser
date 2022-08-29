cmake_minimum_required(VERSION 3.0.0)
project(HTTP_PROCESS_CLOSER VERSION 0.1.0)

if (WIN32)
add_executable(HTTP_PROCESS_CLOSER 
                                main.cpp 
            WindowsAPI/ProcessDispatcher.h WindowsAPI/ProcessDispatcher.cpp
            Listener.h          Listener.cpp
            HandlerRequest.h    HandlerRequest.cpp
            ServerTypes.h       ServerTypes.cpp
            TagWorker.h         TagWorker.cpp)
endif (WIN32)

if (UNIX)
add_executable(HTTP_PROCESS_CLOSER 
                                main.cpp 
            LinuxAPI/ProcessDispatcher.h LinuxAPI/ProcessDispatcher.cpp
            Listener.h          Listener.cpp
            HandlerRequest.h    HandlerRequest.cpp
            ServerTypes.h       ServerTypes.cpp
            TagWorker.h         TagWorker.cpp)
endif (UNIX)
