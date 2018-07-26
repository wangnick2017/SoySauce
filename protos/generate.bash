protoc -I=. --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` Soy.proto
protoc -I=. --cpp_out=. Soy.proto
protoc -I=. --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` Raft.proto
protoc -I=. --cpp_out=. Raft.proto
