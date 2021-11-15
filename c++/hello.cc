#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include "runtime.pb.h"
#include "runtime.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using spec::proto::runtime::v1::Runtime;
using spec::proto::runtime::v1::SayHelloRequest;
using spec::proto::runtime::v1::SayHelloResponse;
using google::protobuf::Any;

std::string layotto_grpc_endpoint() {
      return std::string("127.0.0.1:") + "34904";
}

int main(){
    ClientContext context;
    SayHelloRequest request;
    SayHelloResponse resp;
    std::unique_ptr<Runtime::Stub> client_stub;
    std::string serviceName = "helloworld";
    std::string name = "hello";
    request.set_service_name(serviceName);
    request.set_name(name);
    client_stub = Runtime::NewStub(grpc::CreateChannel(layotto_grpc_endpoint(), grpc::InsecureChannelCredentials()));
    Status status = client_stub->SayHello(&context,request,&resp);
    if (status.ok())
    {
        std::cout << resp.hello() << std::endl;
    }

}