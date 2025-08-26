#include "../include/Transactions/addcredit.h"
#include "../include/frontend.h"

// Constructs AddCredit with a default transaction code of "06"
AddCredit::AddCredit(Frontend& frontend) : Transaction(frontend, "06") {}

void AddCredit::processTransaction() {

    std::cout << "Processing AddCredit Transaction..." << std::endl;

    std::string username; //to search for user
    bool userExists = false;
    User* targetUser;
    User* currentUser = getFrontend().getCurrentUser(); //get user from frontend
    //handle privilage
    if (currentUser->getPrivilege() == "AA") { //bring user info if admin
        std::cout << "Enter username:" << std::endl;
        std::cin >> username  >> std::ws;
        if (getFrontend().getAvailableUsers().size() > 0) {
            for (User* user : getFrontend().getAvailableUsers()) { 
                if (user->getUsername() == username) { //save info if user exists
                    targetUser = user;
                    userExists = true;
                }
            }
        }
    }
    if (currentUser->getPrivilege() == "SS") { //error if user is a seller
        std::cout << "Error: You cannot add credit as a seller." << std::endl;
        return;
    }

    if(!userExists){ //error if user does not exist
        std::cout << "Username not found in the system. Please try again. " << std::endl;
        return;
    }

    double credit;
    std::cout << "Enter credit amount:" << std::endl;
    std::cin >> credit  >> std::ws;
    if (credit < 0 || credit > 1000){ //error if credit is not between 0 - 1000
        std::cout << "Error: Amount of credit added must be between 0 and 1000." << std::endl;
        return;
    }
    
    //add credit to user's current credit
    double currentCredit = targetUser->getCredit();
    currentCredit = currentCredit + credit;
    //update user information with new credit amount
    User* newUser = new User(targetUser->getUsername(), targetUser->getPrivilege(), targetUser->getPassword(), currentCredit);
    delete targetUser;
    targetUser = newUser;

    std::cout << "AddCredit successful: " << *targetUser << std::endl;

    getFrontend().addToDailyTransaction(this);
    return;
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
    os.flush();
    //return(os << "XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC_PPPPPPPPPPPPPPPPPPPPPPPPP");
}
