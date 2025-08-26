#include "../include/Transactions/refund.h"
#include "../include/frontend.h"

// Constructs Refund with a default transaction code of "05"
Refund::Refund(Frontend& frontend) : Transaction(frontend, "05") {}

void Refund::processTransaction() {
    // Checks if the current user is an Admin
    User* currentUser = getFrontend().getCurrentUser();
    if (currentUser->getPrivilege() != "AA") {
        std::cout << "Error: Invalid Transaction. You must be an Admin to use this transaction." << std::endl;
        return;
    }

    std::cout << "Processing Refund Transaction..." << std::endl;

    // Ask for buyer's username
    std::string buyerUsername;
    std::cout << "Enter buyer's username: ";
    std::cin >> buyerUsername;

    //to check if the buyer exists
    if (getFrontend().getAvailableUsers().size() > 0) {
        for (User* user : getFrontend().getAvailableUsers()) {
            if (user->getUsername() != buyerUsername) {
                std::cout << "Error: Invalid Transaction. Buyer's Username already exists." << std::endl;
                return;
            }
        }
    }

    // Ask for seller's username
    std::string sellerUsername;
    std::cout << "Enter seller's username: ";
    std::cin >> sellerUsername;
    
    //to check if the seller exists
    if (getFrontend().getAvailableUsers().size() > 0) {
        for (User* user : getFrontend().getAvailableUsers()) {
            if (user->getUsername() != sellerUsername) {
                std::cout << "Error: Invalid Transaction. Seller's Username already exists." << std::endl;
                return;
            }
        }
    }

    // Ask for transfer amount
    float transferAmount;
    std::cout << "Enter transfer amount: ";
    std::cin >> transferAmount;

    if (transferAmount < 0 || transferAmount > 999999.0) {
        std::cout << "Error: Invalid transfer amount. Amount must be between 0 and 999,999.00." << std::endl;
        return;
    }

    // TODO Transfer credit from seller to buyer
    //      Copy seller to a new User object
    //          Subtract transfer amount from old credit value
    //      Copy buyer to a new User object
    //          Add transfer amount to old credit value
    //      Call Refund buyer & seller setters and set new edited users    

    // TODO Print Refund object to signify successful transaction   

    getFrontend().addToDailyTransaction(this);
}

// TODO Consider removing this function and replace with earlier pseudocode 
// bool Refund::validateUsers() {
//     // TODO fix this, getUserCreditBalance() is not a function.
//     // unordered_map<string, double>& userCreditBalance = getFrontend().getUserCreditBalance();

//     // if (userCreditBalance.find(buyerUsername) == userCreditBalance.end() ||
//     //     userCreditBalance.find(sellerUsername) == userCreditBalance.end()) {
//     //     return false;
//     // }
//     return true;
// }

// TODO Consider removing this function and replace with earlier pseudocode
// void Refund::transferCredit() {
//     unordered_map<string, double>& userCreditBalance = getFrontend().getUserCreditBalance();

//     double buyerBalance = userCreditBalance[buyerUsername];
//     double sellerBalance = userCreditBalance[sellerUsername];

//     if (sellerBalance < transferAmount) {
//         cout << "Error: Seller does not have enough credit to transfer." << endl;
//         return;
//     }

//     sellerBalance -= transferAmount;
//     buyerBalance += transferAmount;

//     userCreditBalance[sellerUsername] = sellerBalance;
//     userCreditBalance[buyerUsername] = buyerBalance;
// }

// Overrides to string method
std::ostream& operator<<(std::ostream& os, const Refund& obj) {
    // TODO implement to fit regex
        
    return (os << "XX_UUUUUUUUUUUUUUU_SSSSSSSSSSSSSSS_CCCCCCCCC");
}
