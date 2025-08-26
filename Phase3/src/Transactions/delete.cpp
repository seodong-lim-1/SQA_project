#include "../include/Transactions/delete.h"
#include "../include/frontend.h"

// Constructs Delete with a default transaction code of "02"
Delete::Delete(Frontend& frontend) : Transaction(frontend, "02") {}

void Delete::processTransaction() {
    // Check if current user is admin
    User* currentUser = getFrontend().getCurrentUser();
    if (currentUser->getPrivilege() != "AA") {
        std::cout << "Error: Invalid Transaction. You must be an Admin to use this transaction." << std::endl;
        return;
    }

	// Input username
	std::string username;
	std::cout << "Input username to delete: " << std::endl; 
	std::cin >> username >> std::ws;

    // Checking if it is a user in the system
    bool UserInSystem = false;
    if (getFrontend().getAvailableUsers().size() > 0) {
        for (User* user : getFrontend().getAvailableUsers()) {
            if (user->getUsername() == username) {
                UserInSystem = true;
            }
        }
    }

    if(UserInSystem == false){
        std::cout << "Username not found in the system. Please try again. " << std::endl;
        return;
    }

    // Checking if user is the current user
    if(currentUser->getUsername() == username){
        std::cout << "Failed to delete, cannot delete oneself" << std::endl;
        return;
    }

    //      Call Delete user setter to set deleted user
    User* Delete::getUser() const {
        return m_user;
    }

    void Delete::setUser(User* user) {
        m_user = user;
    }
    

    // TODO Delete any items owned by deleted user
    //      Get available items from frontend
    //      Iterate through items
    //          If item is owned by deleted user
    //              Delete item
	
    getFrontend().addToDailyTransaction(this);
}

// Overrides to string method
std::ostream& operator<<(std::ostream& os, const Delete& obj) {
    // TODO implement to fit regex
    return (os << "XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC_PPPPPPPPPPPPPPPPPPPPPPPPP");
}