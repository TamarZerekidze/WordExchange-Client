#include "Client.h"
#include <iostream>
#include <cstring>

// Link with ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

Client::Client(const std::string& server_ip, int server_port) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        exit(EXIT_FAILURE);
    }

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation failed\n";
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);

    if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported \n";
        closesocket(client_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

Client::~Client() {
    closesocket(client_socket);
    WSACleanup();
}

bool Client::connectToServer() {
    if (connect(client_socket, reinterpret_cast<struct sockaddr *>(&server_addr), sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed\n";
        closesocket(client_socket);
        WSACleanup();
        return false;
    }
    return true;
}

void Client::sendMessage(const std::string& message) const {
    send(client_socket, message.c_str(), message.length(), 0);
}

std::string Client::receiveMessage() const {
    char buffer[2048] = {0};
    int bytes_received = recv(client_socket, buffer, 2048 , 0);
    if (bytes_received > 0) {
        return std::string(buffer, bytes_received);
    }
    return "";
}

void Client::closeConnection() const {
    closesocket(client_socket);
}
