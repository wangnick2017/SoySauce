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

set(Boost_USE_STATIC_LIBS FALSE)
find_package(Boost REQUIRED
        COMPONENTS thread log chrono unit_test_framework)
include_directories(${Boost_INCLUDE_DIR})
add_definitions(
        -D BOOST_THREAD_VERSION=4
        -D BOOST_LOG_DYN_LINK
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