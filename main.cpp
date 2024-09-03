#include "Client.h"
#include <iostream>

int main() {
    Client client("127.0.0.1", 54000);

    if (!client.connectToServer()) {
        std::cerr << "Failed to connect to server\n";
        return -1;
    }

    std::string response = client.receiveMessage();
    std::cout << response;

    while (true) {

        std::string user_input;
        std::getline(std::cin, user_input);
        client.sendMessage(user_input + "\n");

        response = client.receiveMessage();
        if (response.find("different") == std::string::npos) system("cls");
        std::cout << response;

        if (response.find("Disconnecting...") != std::string::npos) {
            break;
        }
    }

    client.closeConnection();
    return 0;
}
