// client.cpp
#include <grpcpp/grpcpp.h>
#include "FileTransfer.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using FileTransfer::FileTransferService;
using FileTransfer::UploadRequest;
using FileTransfer::UploadResponse;
using FileTransfer::DownloadRequest;
using FileTransfer::DownloadResponse;

class FileTransferClient {
public:
    FileTransferClient(std::shared_ptr<Channel> channel) : stub_(FileTransferService::NewStub(channel)) {}

    std::string UploadFile(const std::string& file_path) {
        // Implement file upload logic
        // Read file from file_path and send its content to server
    }

    void DownloadFile(const std::string& file_name, const std::string& save_path) {
        // Implement file download logic
        // Request file with name file_name from server and save its content to save_path
    }

private:
    std::unique_ptr<FileTransferService::Stub> stub_;
};

int main(int argc, char** argv) {
    FileTransferClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    // Use client.UploadFile and client.DownloadFile to interact with the server
    return 0;
}
