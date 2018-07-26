cmake_minimum_required(VERSION 3.10)

project(SoySauce)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS
        chrono
        thread
        log
        )

if(NOT Boost_FOUND)
    message("Not found Boost")
endif()

include_directories(${Boost_INCLUDE_DIRS})

include_directories(
        include
        include/Rpc
        include/Raft
        include/Raft/Rpc
        include/Raft/Role
)

add_subdirectory(protos)
add_subdirectory(src)