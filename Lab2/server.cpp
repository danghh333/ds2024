// server.cpp
#include <grpcpp/grpcpp.h>
#include "FileTransfer.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using FileTransfer::FileTransferService;
using FileTransfer::UploadRequest;
using FileTransfer::UploadResponse;
using FileTransfer::DownloadRequest;
using FileTransfer::DownloadResponse;

class FileTransferServiceImpl final : public FileTransferService {
    Status UploadFile(ServerContext* context, const UploadRequest* request, UploadResponse* response) override {
        // Implement file upload logic
        // Save file content received in request->file_content to a new file with name request->file_name
        return Status::OK;
    }

    Status DownloadFile(ServerContext* context, const DownloadRequest* request, DownloadResponse* response) override {
        // Implement file download logic
        // Read file with name request->file_name and send its content in response->file_content
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    FileTransferServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main() {
    RunServer();
    return 0;
}

sudo protoc -I=. --cpp_out=. --grpc_out=. --plugin=protoc-gen-grpc=/usr/local/bin FileTransfer.proto