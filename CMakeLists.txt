cmake_minimum_required(VERSION 3.0.0)
project(HTTP_PROCESS_CLOSER VERSION 0.1.0)

add_executable(HTTP_PROCESS_CLOSER 
                                main.cpp 
            ProcessDispatcher.h ProcessDispatcher.cpp
            Listener.h          Listener.cpp)
