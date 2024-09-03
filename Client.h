#ifndef CLIENT_H
#define CLIENT_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

class Client {
private:
    SOCKET client_socket;
    struct sockaddr_in server_addr;

public:
    Client(const std::string& server_ip, int server_port);
    ~Client();

    bool connectToServer();
    void sendMessage(const std::string& message) const;
    [[nodiscard]] std::string receiveMessage() const;
    void closeConnection() const;
};

#endif // CLIENT_H

