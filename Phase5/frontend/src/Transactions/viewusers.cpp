#include "../include/Transactions/viewusers.h"
#include "../include/frontend.h"

// Constructs ViewUsers with no transaction code
ViewUsers::ViewUsers(Frontend& frontend) : Transaction(frontend, "") {}

void ViewUsers::processTransaction() {
    std::cout << "Processing ViewUsers Transaction..." << std::endl;

    // Checks if the current user is not an Admin
      User* currentUser = getFrontend().getCurrentUser();
      if (currentUser->getPrivilege() != "AA") {
          std::cout << "Error: Invalid Transaction. User lacks privilege." << std::endl;
            std::cout << "ViewUsers cancelled." << std::endl;
          return;
      }

    // Gets all available users 
    const std::vector<User*>& users = getFrontend().getAvailableUsers();

    // Prints out all users  
    std::cout << "|-----------------------------------------|" << std::endl;
    std::cout << "| Username        | Privilege | Credit    |" << std::endl;
    std::cout << "|-----------------------------------------|" << std::endl;
    for (User* user : users) {
      std::cout << "| " <<  std::left << std::setw(15) << user->getUsername() << " | ";
      std::cout << std::left << std::setw(9) << user->getPrivilege() << " | "; 
      std::cout << std::left << std::setw(9) << std::fixed << std::setprecision(2) << user->getCredit()  << " | " << std::endl; 
    }
    std::cout << "|-----------------------------------------|" << std::endl;
}