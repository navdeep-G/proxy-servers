#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void handle_client(int client_socket) {
    char buffer[1024];
    recv(client_socket, buffer, sizeof(buffer), 0);
    
    std::string request(buffer);
    std::string delimiter = " ";
    std::string url = request.substr(request.find(delimiter) + 1);
    url = url.substr(0, url.find(delimiter));

    std::string host;
    int port = 80;
    size_t host_start = url.find("://") + 3;
    size_t port_start = url.find(":", host_start);
    size_t path_start = url.find("/", host_start);

    if (port_start != std::string::npos) {
        host = url.substr(host_start, port_start - host_start);
        port = std::stoi(url.substr(port_start + 1, path_start - port_start - 1));
    } else {
        host = url.substr(host_start, path_start - host_start);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &server_addr.sin_addr);

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

    send(server_socket, buffer, sizeof(buffer), 0);
    int bytes_received;
    while ((bytes_received = recv(server_socket, buffer, sizeof(buffer), 0)) > 0) {
        send(client_socket, buffer, bytes_received, 0);
    }

    close(server_socket);
    close(client_socket);
}

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);

    std::cout << "Proxy server listening on port 8888" << std::endl;

    while (true) {
        int client_socket = accept(server_socket, NULL, NULL);
        std::thread(handle_client, client_socket).detach();
    }

    close(server_socket);
    return 0;
}
