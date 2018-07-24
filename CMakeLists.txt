cmake_minimum_required(VERSION 3.10)
project(SoySauce)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS
        chrono
        thread
        )
if(NOT Boost_FOUND)
    message("Not found Boost")
endif()

include_directories(${Boost_INCLUDE_DIRS})



ADD_SUBDIRECTORY(src)