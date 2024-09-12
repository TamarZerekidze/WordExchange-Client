#include "Client.h"
#include <iostream>
#include <unordered_set>

#define BUF_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 55000


int main() {
    Client client("127.0.0.1", 55000);

    if (!client.connectToServer()) {
        std::cerr << "Failed to connect to server\n";
        return -1;
    }

    static const std::unordered_set<std::string> messageKeywords = {
        "Waiting for another player",
        "No partner found within the timeout.",
        "Login successful!",
        "Game is starting...",
        "Timeout occurred",
        "It seems that ",
        "Your word recorded.",
        "Invalid input. Please enter a valid word.",
        "Congratulations, both of you",
        "do not match!",
        "Both words taken in!",
        "stats and leaderboard:",
        "Game Session flow:"
    };
    while (true) {

        std::string response = client.receiveMessage();
        std::cout << response;

        if (response.find("Disconnecting") != std::string::npos) {
            break; // Break the loop if the player is disconnected
        }
        auto skipping = false;
        for (const auto& keyword : messageKeywords) {
            if (response.find(keyword) != std::string::npos) {
                 skipping = true; // Continue the loop
                break;
            }
        }
        if (skipping) continue;

        std::string user_input;
        std::getline(std::cin, user_input);
        client.sendMessage(user_input + "\n");
    }

    client.closeConnection();
    return 0;
}
