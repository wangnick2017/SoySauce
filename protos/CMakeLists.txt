execute_process(
        COMMAND bash ./generate.bash
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

function(move FILENAME TARGET_DIR)
    file(RENAME ${FILENAME} "${TARGET_DIR}/${FILENAME}")
endfunction()

move("Soy.grpc.pb.h" "../include/Rpc")
move("Soy.pb.h" "../include/Rpc")
move("Raft.grpc.pb.h" "../include/Raft/Rpc")
move("Raft.pb.h" "../include/Raft/Rpc")

move("Soy.grpc.pb.cc" "../src/Rpc")
move("Soy.pb.cc" "../src/Rpc")
move("Raft.grpc.pb.cc" "../src/Raft/Rpc")
move("Raft.pb.cc" "../src/Raft/Rpc")