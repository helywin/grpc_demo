/*********************************************************************************
 * FileName: publisher.cpp
 * Author: helywin <jiang770882022@hotmail.com>
 * Version: 0.0.1
 * Date: 2022-07-19 下午7:05
 * Description: 
 * Others:
*********************************************************************************/


#include <protos/helloworld.pb.h>
#include <protos/helloworld.grpc.pb.h>

#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>

#include <iostream>

class HelloWorldService final : public test1::TestService::Service {
public:
    grpc::Status getDataStream(::grpc::ServerContext *context, const ::test1::Data *request,
                               ::grpc::ServerWriter<::test1::MsgReply> *writer) override
    {
        for (int i = 0; i < 10; ++i) {
            test1::MsgReply reply{};
            reply.set_message(std::string("hello at ") + std::to_string(i));
            writer->Write(reply);
            usleep(1e6);
        }
        return grpc::Status::OK;
    }

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