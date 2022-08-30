cmake_minimum_required(VERSION 3.0.0)
project(HTTP_PROCESS_CLOSER VERSION 0.1.0)

set(BUILD_SERVER FALSE)
set(BUILD_CLIENT FALSE)

if(BUILD_CLIENT)
    add_subdirectory(client-side)
endif()

if(BUILD_SERVER)
    add_subdirectory(server-side)
endif()
