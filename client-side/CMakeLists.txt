list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/main.cpp 
                          ${CMAKE_CURRENT_LIST_DIR}/ClientUI.cpp
                          ${CMAKE_CURRENT_LIST_DIR}/ClientTypes.cpp)

if (WIN32)
    list(APPEND myApp_INCLUDES ${CMAKE_CURRENT_LIST_DIR} 
                               ${CMAKE_CURRENT_LIST_DIR}/WindowsAPI)
    list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/LinuxAPI/ServerConnector.cpp)

endif (WIN32)

if (UNIX)
    list(APPEND myApp_INCLUDES ${CMAKE_CURRENT_LIST_DIR} 
                               ${CMAKE_CURRENT_LIST_DIR}/LinuxAPI)

    list(APPEND myApp_SOURCES ${CMAKE_CURRENT_LIST_DIR}/LinuxAPI/ServerConnector.cpp)
endif(UNIX)

