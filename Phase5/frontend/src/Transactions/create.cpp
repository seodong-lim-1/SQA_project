#include "../include/Transactions/create.h"
#include "../include/frontend.h"
#include "../include/Users/admin.h"
#include "../include/Users/buystandard.h"
#include "../include/Users/fullstandard.h"
#include "../include/Users/sellstandard.h"

// Constructs Create with a default transaction code of "01"
Create::Create(Frontend& frontend) : Transaction(frontend, "01") {}

void Create::processTransaction() {
    std::cout << "Processing Create Transaction..." << std::endl;

    // Checks if the current user is an Admin
    User* currentUser = getFrontend().getCurrentUser();
    if (currentUser->getPrivilege() != "AA") {
        std::cout << "Error: Invalid Transaction. You must be an Admin to use this transaction." << std::endl;
        std::cout << "Create cancelled." << std::endl;
        return;
    }

    // Gets new username
    std::string tempUsername;
    std::cout << "Enter new username: " << std::endl;
    std::cin >> tempUsername >> std::ws;

    // Checks if the new username is too long
    if (tempUsername.length() > 15) {
        std::cout << "Error: Invalid Transaction. Username must be less than 15 characters." << std::endl;
        std::cout << "Create cancelled." << std::endl;
        return;
    }

    // Checks if new username already exists
    if (getFrontend().getAvailableUsers().size() > 0) {
        for (User* user : getFrontend().getAvailableUsers()) {
            if (user->getUsername() == tempUsername) {
                std::cout << "Error: Invalid Transaction. Username already exists." << std::endl;
                std::cout << "Create cancelled." << std::endl;
                return;
            }
        }
    }

    // Gets new user type
    std::string tempUserType;
    std::cout << "Enter new user type (AA, FS, BS, SS): " << std::endl;
    std::cin >> tempUserType >> std::ws;

    // Checks if the new user type is valid
    if (tempUserType != "AA" && tempUserType != "FS" && tempUserType != "BS" && tempUserType != "SS") {
        std::cout << "Error: Invalid Transaction. User type must be AA, FS, BS, or SS." << std::endl;
        std::cout << "Create cancelled." << std::endl;
        return;
    }

    // Gets new user password
    std::string tempPassword;
    std::cout << "Enter new user password: " << std::endl;
    std::cin >> tempPassword >> std::ws;
    std::string hashedPassword = getFrontend().hashString(tempPassword);
    
    // Creates a new user:
    User* newUser;
    if (tempUserType == "AA") {
        newUser = new Admin(tempUsername, hashedPassword, 0);
    } else if (tempUserType == "FS") {
        newUser = new FullStandard(tempUsername, hashedPassword, 0);
    } else if (tempUserType == "BS") {
        newUser = new BuyStandard(tempUsername, hashedPassword, 0);
    } else if (tempUserType == "SS") {
        newUser = new SellStandard(tempUsername, hashedPassword, 0);
    }
    setNewUser(newUser);

    std::cout << "Create successful: " << *newUser << std::endl;

    getFrontend().addToDailyTransaction(this);
}

User* Create::getNewUser() const {
    return m_newUser;
}

void Create::setNewUser(User* user) {
    m_newUser = user;
}

// Overrides to string method
std::ostream& operator<<(std::ostream& os, const Create& obj) {
    const User* user = obj.getNewUser();
    
    return (os << obj.getTransactionCode() << " " << *user);
}