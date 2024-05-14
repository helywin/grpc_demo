/*********************************************************************************
 * FileName: subscriber.cpp
 * Author: helywin <jiang770882022@hotmail.com>
 * Version: 0.0.1
 * Date: 2022-07-19 下午7:05
 * Description: 
 * Others:
*********************************************************************************/

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
    auto reader = stub->getDataStream(&context, data);
    test1::MsgReply reply{};
    while (reader->Read(&reply)) {
        std::cout << "I got message: " << reply.message() << std::endl;
    }

    return 0;
}