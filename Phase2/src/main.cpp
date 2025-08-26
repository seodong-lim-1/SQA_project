#include "../include/Transactions/login.h"
#include "../include/frontend.h"
#include <iostream>

Frontend frontend;
std::fstream* availableUsers;
std::fstream* availableItems;

int main() {
    std::cout << "Press Ctrl+C to terminate the program." << std::endl;

    while (true) {
        std::string input;
        std::cin >> input;

        if (input == "login") {
            Login login;

            frontend.start = login.startFrontend();
            availableUsers = frontend.readCurrentUsers();
            login.availableUsers = availableUsers;
            
            if(frontend.start){
                login.processTransaction();
                if(login.acceptanceFlag){
                    frontend.currentUser = login.username;
                    availableItems = frontend.readAvailableItems();
                    std::cout << "Welcome " << frontend.currentUser << std::endl;
                }
            }
        }
        else {
            std::cout << "Invalid input" << std::endl;
        }
    } 
}
