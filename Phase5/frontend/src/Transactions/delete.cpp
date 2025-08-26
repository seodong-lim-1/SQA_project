#include "../include/Transactions/delete.h"
#include "../include/frontend.h"

// Constructs Delete with a default transaction code of "02"
Delete::Delete(Frontend& frontend) : Transaction(frontend, "02") {}

void Delete::processTransaction() {
    std::cout << "Processing Delete Transaction..." << std::endl;

    // Check if current user is admin
    User* currentUser = getFrontend().getCurrentUser();
    if (currentUser->getPrivilege() != "AA") {
        std::cout << "Error: Invalid Transaction. User lacks privilege." << std::endl;
        std::cout << "Delete cancelled." << std::endl;
        return;
    }

	// Ask for username to delete
	std::string username;
	std::cout << "Enter username:" << std::endl; 
	std::cin >> username >> std::ws;

    // Checks if user exists
    bool userFound = false;
    for (User* user : getFrontend().getAvailableUsers()) {
        if (user->getUsername() == username) {
            setOldUser(user);
            userFound = true;
            break;
        }
    }
    if (!userFound) {
        std::cout << "Error: Invalid Transaction. User does not exist." << std::endl;
        std::cout << "Delete cancelled." << std::endl;
        return;
    }   

    // Checks if user is trying to delete themselves
    if (getOldUser()->getUsername() == currentUser->getUsername()) {
        std::cout << "Error: Invalid Transaction. Cannot delete yourself." << std::endl;
        std::cout << "Delete cancelled." << std::endl;
        return;
    }

    std::cout << "Delete successful: " << *getOldUser() << std::endl;
	
    getFrontend().addToDailyTransaction(this);
}

User* Delete::getOldUser() const {
    return m_oldUser;
}

void Delete::setOldUser(User* user) {
    m_oldUser = user;
}

// Overrides to string method
std::ostream& operator<<(std::ostream& os, const Delete& obj) {
    User* user = obj.getOldUser();

    return (os << obj.getTransactionCode() << " " << *user);
}