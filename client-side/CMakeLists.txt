# if (WIN32)
#     add_executable(${PROJECT_NAME} 
#                                 main.cpp 
#                 )
# endif (WIN32)

if (UNIX)
    list(APPEND myApp_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp 
        ${CMAKE_CURRENT_LIST_DIR}/ServerConnector.h            ${CMAKE_CURRENT_LIST_DIR}/ServerConnector.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ClientUI.h                   ${CMAKE_CURRENT_LIST_DIR}/ClientUI.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ClientTypes.h                ${CMAKE_CURRENT_LIST_DIR}/ClientTypes.cpp)
endif(UNIX)

