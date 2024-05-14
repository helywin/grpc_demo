cmake_minimum_required(VERSION 3.18)
project(grpc_demo)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC REQUIRED)

set(PROTO_FILES
        protos/helloworld.proto
        )
add_library(proto ${PROTO_FILES})
target_link_libraries(proto
        PUBLIC
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
        z # zlib
        )

target_include_directories(proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET proto LANGUAGE cpp)
protobuf_generate(TARGET proto LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")

add_subdirectory(server)