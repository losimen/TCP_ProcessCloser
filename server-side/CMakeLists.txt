
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
    list(APPEND myApp_INCLUDES ${CMAKE_CURRENT_LIST_DIR} 
                               ${CMAKE_CURRENT_LIST_DIR}/LinuxAPI)

    list(APPEND myApp_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/LinuxAPI/ProcessDispatcher.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LinuxAPI/Listener.cpp
    ${CMAKE_CURRENT_LIST_DIR}/HandlerRequest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ServerTypes.cpp)
endif (UNIX)

# include_directories(${SHARED_INCLUDES})
