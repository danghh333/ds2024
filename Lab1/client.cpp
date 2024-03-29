#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // Create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cerr << "Socket creation failed\n";
        return 1;
    }

    // Connect to server
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); // Port number
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) == -1) {
        std::cerr << "Invalid address/ Address not supported\n";
        return 1;
    }

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Connection failed\n";
        return 1;
    }

    // Send and receive data
    char buffer[1024] = {0};
    recv(client_socket, buffer, 1024, 0);
    std::cout << "Message received from server: " << buffer << std::endl;

    strcpy(buffer, "Hello from client");
    send(client_socket, buffer, strlen(buffer), 0);
    std::cout << "Message sent to server\n";

    // Close socket
    close(client_socket);

    return 0;
}
