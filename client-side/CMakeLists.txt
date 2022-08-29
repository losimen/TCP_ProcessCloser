if (WIN32)
add_executable(${PROJECT_NAME} 
                            main.cpp 
              )
endif (WIN32)

if (UNIX)
add_executable(${PROJECT_NAME} 
                                           main.cpp 
              ServerConnector.h            ServerConnector.cpp
              ClientUI.h                   ClientUI.cpp
              ClientTypes.h
              )
endif(UNIX)

