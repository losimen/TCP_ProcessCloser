set(APP_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

if (WIN32)
    set(SHARED_INCLUDES ${APP_ROOT_DIR} 
                        ${APP_ROOT_DIR}/WindowsAPI)
    add_executable(${PROJECT_NAME} 
                                            main.cpp 
                WindowsAPI/ProcessDispatcher.h WindowsAPI/ProcessDispatcher.cpp
                WindowsAPI/Listener.h          WindowsAPI/Listener.cpp
                HandlerRequest.h               HandlerRequest.cpp
                ServerTypes.h                  ServerTypes.cpp
                TagWorker.h                    TagWorker.cpp)
endif (WIN32)

if (UNIX)
    set(SHARED_INCLUDES ${APP_ROOT_DIR} 
                        ${APP_ROOT_DIR}/LinuxAPI)
    add_executable(${PROJECT_NAME} 
                                            main.cpp 
                LinuxAPI/ProcessDispatcher.h LinuxAPI/ProcessDispatcher.cpp
                LinuxAPI/Listener.h          LinuxAPI/Listener.cpp
                HandlerRequest.h             HandlerRequest.cpp
                ServerTypes.h                ServerTypes.cpp
                TagWorker.h                  TagWorker.cpp)
endif (UNIX)

include_directories(${SHARED_INCLUDES})
