#include "../include/Transactions/addcredit.h"
#include "../include/Transactions/advertise.h"
#include "../include/Transactions/bid.h"
#include "../include/Transactions/create.h"
#include "../include/Transactions/delete.h"
#include "../include/Transactions/login.h"
#include "../include/Transactions/logout.h"
#include "../include/Transactions/refund.h"
#include "../include/Transactions/viewauctions.h"
#include "../include/Transactions/viewusers.h"

#include "../include/frontend.h"
#include <iostream>


int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Error: Invalid number of arguments. Expected 3, got " << argc-1 << "." << std::endl;
        std::cout << "Usage: ./auctions-system <available_users_file> <available_items_file> <daily_transaction_file>" << std::endl;
        return 1;
    }

    Frontend frontend(argv[1], argv[2], argv[3]);

    std::string input;
    while (std::getline(std::cin, input)) {

        // If frontend is not active, only login is accepted
        if (!frontend.getIsActive() && input != "login") {
            std::cout << "Error: Invalid Transaction. Must login first." << std::endl;
            continue;
        }

        if (input == "addcredit"){
            AddCredit* addCredit = new AddCredit(frontend);
            addCredit->processTransaction();
        }
        else if (input == "advertise"){
            Advertise* advertise = new Advertise(frontend);
            advertise->processTransaction();
        }
        else if (input == "bid"){
            Bid* bid = new Bid(frontend);
            bid->processTransaction();
        }
        else if (input == "create"){
            Create* create = new Create(frontend);
            create->processTransaction();
        }
        else if (input == "delete"){
            Delete deleteTransaction(frontend);
            deleteTransaction.processTransaction();    
        }
        else if (input == "login" && frontend.getAllowLogin()) {
            Login* login = new Login(frontend);
            login->processTransaction();
        }
        else if (input == "logout" && frontend.getAllowLogout()){
            Logout* logout = new Logout(frontend);
            logout->processTransaction();

            return 0; // Exits program
        }
        else if (input == "refund"){
            Refund* refund = new Refund(frontend);
            refund->processTransaction();
        }
        else if (input == "viewauctions"){
            ViewAuctions* viewAuctions = new ViewAuctions(frontend);
            viewAuctions->processTransaction();
        }
        else if (input == "viewusers"){
            ViewUsers* viewUsers = new ViewUsers(frontend);
            viewUsers->processTransaction();    
        }
        else {
            // TODO handle edge cases/constraints
            std::cout << "Error: Invalid Transaction. Transaction does not exist." << std::endl;
        }
    } 
}
