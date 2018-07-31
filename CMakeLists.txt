cmake_minimum_required(VERSION 3.10)

project(SoySauce)

set(CMAKE_CXX_STANDARD 17)


include_directories(
        include
        include/Rpc
        include/Raft
        include/Raft/Rpc
        include/Raft/Role
)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake;${CMAKE_MODULE_PATH}")


include_directories(${Boost_INCLUDE_DIRS})
find_package(Boost REQUIRED COMPONENTS
        chrono
        thread
        log
)
if(NOT Boost_FOUND)
    message("Not found Boost")
endif()


find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})


find_package(GRPC REQUIRED)
include_directories(${GRPC_INCLUDE_DIR})


add_subdirectory(protos)
add_subdirectory(src)