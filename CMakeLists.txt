cmake_minimum_required(VERSION 3.0.0)
project(HTTP_PROCESS_CLOSER VERSION 0.1.0)

option(BUILD_SERVER "Enable building server-side" OFF)
option(BUILD_CLIENT "Enable building client-side" ON)

if(BUILD_CLIENT)
    add_subdirectory(client-side)
endif()

if(BUILD_SERVER)
    add_subdirectory(server-side)
endif()
