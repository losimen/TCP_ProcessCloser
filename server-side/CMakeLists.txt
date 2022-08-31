
list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/main.cpp 
                          ${CMAKE_CURRENT_LIST_DIR}/HandlerRequest.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/ServerTypes.cpp)


if (WIN32)
    list(APPEND myApp_INCLUDES ${CMAKE_CURRENT_LIST_DIR} 
                               ${CMAKE_CURRENT_LIST_DIR}/WindowsAPI)

    list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/WindowsAPI/ProcessDispatcher.cpp
                              ${CMAKE_CURRENT_LIST_DIR}/WindowsAPI/Listener.cpp)
endif (WIN32)

if (UNIX)
    list(APPEND myApp_INCLUDES ${CMAKE_CURRENT_LIST_DIR} 
                               ${CMAKE_CURRENT_LIST_DIR}/LinuxAPI)

    list(APPEND myApp_SOURCES  ${CMAKE_CURRENT_LIST_DIR}/LinuxAPI/ProcessDispatcher.cpp
                               ${CMAKE_CURRENT_LIST_DIR}/LinuxAPI/Listener.cpp)
endif (UNIX)
