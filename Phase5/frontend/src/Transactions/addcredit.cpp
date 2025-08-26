#include "../include/Transactions/addcredit.h"
#include "../include/frontend.h"

// Constructs AddCredit with a default transaction code of "06"
AddCredit::AddCredit(Frontend& frontend) : Transaction(frontend, "06") {}

void AddCredit::processTransaction() {
    std::cout << "Processing AddCredit Transaction..." << std::endl;

    // Handles privilege checking
    User* currentUser = getFrontend().getCurrentUser();
    User* targetUser;
    bool userFound = false;
    if (currentUser->getPrivilege() == "AA") {
        std::string username; 
        std::cout << "Enter username:" << std::endl;
        std::cin >> username  >> std::ws;

        // Checks if the username exists and gets user if it does
        if (getFrontend().getAvailableUsers().size() > 0) {
            for (User* user : getFrontend().getAvailableUsers()) {
                if (user->getUsername() == username) {
                    targetUser = user;
                    userFound = true;
                }
            }
        }
    }
    else if (currentUser->getPrivilege() == "FS" || currentUser->getPrivilege() == "BS") {
        targetUser = currentUser;
        userFound = true;
    }
    else {
        std::cout << "Error: Invalid Transaction. User lacks privilege." << std::endl;
        std::cout << "AddCredit cancelled." << std::endl;
        return;
    }

    // Checks if user exists
    if (!userFound) {
        std::cout << "Error: Invalid Transaction. Username does not exist." << std::endl;
        std::cout << "AddCredit cancelled." << std::endl;
        return;
    }

    // Gets credit amount
    float credit;
    std::cout << "Enter credit amount:" << std::endl;
    std::cin >> credit  >> std::ws;

    // Checks if credit amount is valid (between 0 and 1000)
    if (credit < 0 || credit > 1000){
        std::cout << "Error: Invalid Transaction. Credit amount must be between $0.00 and $1000.00." << std::endl;
        std::cout << "AddCredit cancelled." << std::endl;
        return;
    }
    
    // Creates an edited user with the new credit amount
    float newCredit = targetUser->getCredit() + credit;
    User* newEditedUser = new User(targetUser->getUsername(), targetUser->getPrivilege(),  targetUser->getPassword(), newCredit);
    setEditedUser(newEditedUser);

    std::cout << "AddCredit successful: " << *newEditedUser << std::endl;

    getFrontend().addToDailyTransaction(this);
}

User* AddCredit::getEditedUser() const {
    return m_editedUser;
}

void AddCredit::setEditedUser(User* user) {
    m_editedUser = user;
}

// Overrides to string method
std::ostream& operator<<(std::ostream& os, const AddCredit& obj) {
    const User* user = obj.getEditedUser();
    
    return (os << obj.getTransactionCode() << " " << *user);
}
