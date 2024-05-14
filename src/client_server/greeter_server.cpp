//
// Created by helywin on 2022/7/18.
//

#include <protos/helloworld.pb.h>
#include <protos/helloworld.grpc.pb.h>

#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>

#include <iostream>

class HelloWorldService final : public test1::TestService::Service {
public:
    grpc::Status getData(::grpc::ServerContext *context, const ::test1::Data *request,
                         ::test1::MsgReply *response) override
    {
        response->set_message(std::string("hello at ") + std::to_string(request->data()));
        return grpc::Status::OK;
    }
};

int main(int argc, char* argv[])
{
    grpc::ServerBuilder builder;
    builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());

    HelloWorldService my_service;
    builder.RegisterService(&my_service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    server->Wait();

    return 0;
}