cmake_minimum_required(VERSION 3.0.0)
project(HTTP_PROCESS_CLOSER VERSION 0.1.0)

include(services/CMakeLists.txt)
add_subdirectory(services)

set(BUILD_SERVER FALSE)
set(BUILD_CLIENT TRUE)

if(BUILD_CLIENT)
    include(client-side/CMakeLists.txt)
    add_subdirectory(client-side)
    add_executable(HTTP_PROCESS_CLOSER ${myApp_SOURCES})
endif()

if(BUILD_SERVER)
    include(server-side/CMakeLists.txt)
    add_subdirectory(server-side)
    add_executable(HTTP_PROCESS_CLOSER ${myApp_SOURCES})
endif()

include_directories(${myApp_INCLUDES})
