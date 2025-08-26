#include "../include/Transactions/login.h"
#include "../include/frontend.h"
#include <iostream>

bool Login::startFrontend() {
    return true;
}

void Login::processTransaction() {
    // Gets username from user
    std::cout << "Enter username: ";
    std::cin >> Login::username;

    // Checks if user exists
    std::string line;
    bool userExists = false;
    while (getline(*Login::availableUsers, line)) {
        if (line.find(Login::username) != std::string::npos) {
            userExists = true;
            break;
        }
    }

    // Processes accepted user
    if (userExists) {
        std::cout << "Welcome back, " << username << std::endl;
        Login::acceptanceFlag = true;
        // TODO no transaction other than login should be accepted before a login
        // TODO no subsequent login should be accepted after a login, until after a logout
        // TODO after a non-admin login, only unprivileged transactions are accepted
        // TODO after an admin login, all transactions are accepted
    } else {
        std::cout << "Error: Invalid Transaction. User does not exist." << std::endl;
    }
    
}
