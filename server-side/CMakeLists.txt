if (WIN32)
add_executable(${PROJECT_NAME} 
                                main.cpp 
            WindowsAPI/ProcessDispatcher.h WindowsAPI/ProcessDispatcher.cpp
            WindowsAPI/Listener.h          WindowsAPI/Listener.cpp
            HandlerRequest.h    HandlerRequest.cpp
            ServerTypes.h       ServerTypes.cpp
            TagWorker.h         TagWorker.cpp)
endif (WIN32)

if (UNIX)
add_executable(${PROJECT_NAME} 
                                main.cpp 
            LinuxAPI/ProcessDispatcher.h LinuxAPI/ProcessDispatcher.cpp
            LinuxAPI/Listener.h          LinuxAPI/Listener.cpp
            HandlerRequest.h    HandlerRequest.cpp
            ServerTypes.h       ServerTypes.cpp
            TagWorker.h         TagWorker.cpp)
endif (UNIX)

