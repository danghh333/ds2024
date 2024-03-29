#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // Create socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Socket creation failed\n";
        return 1;
    }

    // Bind socket
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080); // Port number

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Bind failed\n";
        return 1;
    }

    // Listen
    if (listen(server_socket, 5) == -1) {
        std::cerr << "Listen failed\n";
        return 1;
    }

    // Accept connection
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
    if (client_socket == -1) {
        std::cerr << "Accept failed\n";
        return 1;
    }

    // Send and receive data
    char buffer[1024] = {0};
    strcpy(buffer, "Hello from server");
    send(client_socket, buffer, strlen(buffer), 0);
    std::cout << "Message sent to client\n";

    recv(client_socket, buffer, 1024, 0);
    std::cout << "Message received from client: " << buffer << std::endl;

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}