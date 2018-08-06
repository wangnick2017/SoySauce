include_directories(
        ${CMAKE_CURRENT_LIST_DIR}
)

file(GLOB_RECURSE LIB_SOURCE *.cpp *.cc)

#add_library(${PROJECT_NAME} STATIC ${LIB_SOURCE} ${INCLUDE_DIRECTORIES})
add_executable(${PROJECT_NAME} ${LIB_SOURCE})

target_link_libraries(
        ${PROJECT_NAME}
        ${Boost_LIBRARIES}
        ${PROTOBUF_LIBRARIES}
        ${GRPC_LIBRARIES}
)