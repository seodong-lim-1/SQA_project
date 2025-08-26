#include "../include/Transactions/logout.h"
#include "../include/frontend.h"

// Constructs Logout with a default transaction code of "00" for End Of Session
Logout::Logout(Frontend& frontend) : Transaction(frontend, "00") {}

void Logout::processTransaction() {
    getFrontend().setIsActive(false);
    getFrontend().setAllowLogin(true);
    getFrontend().setAllowLogout(false);

    getFrontend().addToDailyTransaction(this);

    getFrontend().writeDailyTransaction();

    std::cout << "Goodbye, thank you for visiting!" << std::endl;
}

// Overrides to string method
std::ostream& operator<<(std::ostream& os, const Logout& obj) {
    const User* currentUser = obj.getFrontend().getCurrentUser();
    
    return (os << obj.getTransactionCode() << " " << *currentUser);
}