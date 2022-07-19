//
// Created by helywin on 2022/7/18.
//


#include <protos/helloworld.pb.h>
#include <protos/helloworld.grpc.pb.h>

#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>

#include <iostream>


int main(int argc, char* argv[])
{
    // Setup request
    test1::Data data;
    test1::MsgReply result;
    data.set_data(1);

    // Call
    auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    std::unique_ptr<test1::TestService::Stub> stub = test1::TestService::NewStub(channel);
    grpc::ClientContext context;
    grpc::Status status = stub->getData(&context, data, &result);

    // Output result
    std::cout << "I got message:" << std::endl;
    std::cout << result.message() << std::endl;
    return 0;
}