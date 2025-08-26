#include "../include/Transactions/refund.h"
#include "../include/frontend.h"

// Constructs Refund with a default transaction code of "05"
Refund::Refund(Frontend& frontend) : Transaction(frontend, "05") {}

void Refund::processTransaction() {
    std::cout << "Processing Refund Transaction..." << std::endl;

    // Checks if the current user is not an Admin
    User* currentUser = getFrontend().getCurrentUser();
    if (currentUser->getPrivilege() != "AA") {
        std::cout << "Error: Invalid Transaction. User lacks privilege." << std::endl;
        std::cout << "Refund cancelled." << std::endl;
        return;
    }

    // Ask for buyer's username
    std::string buyerUsername;
    std::cout << "Enter buyer's username: " << std::endl;
    std::cin >> buyerUsername >> std::ws;

    // Checks if buyer exists
    bool buyerFound = false;
    for (User* user : getFrontend().getAvailableUsers()) {
        if (user->getUsername() == buyerUsername) {
            buyerFound = true;
            break;
        }
    }
    if (!buyerFound) {
        std::cout << "Error: Invalid Transaction. Buyer does not exist." << std::endl;
        std::cout << "Refund cancelled." << std::endl;
        return;
    }

    // Ask for seller's username
    std::string sellerUsername;
    std::cout << "Enter seller's username: " << std::endl;
    std::cin >> sellerUsername >> std::ws;
    
    // Checks if seller exists
    bool sellerFound = false;
    for (User* user : getFrontend().getAvailableUsers()) {
        if (user->getUsername() == sellerUsername) {
            sellerFound = true;
            break;
        }
    }
    if (!sellerFound) {
        std::cout << "Error: Invalid Transaction. Seller does not exist." << std::endl;
        std::cout << "Refund cancelled." << std::endl;
        return;
    }

    // Ask for refund amount
    float refundAmount;
    std::cout << "Enter refund amount: " << std::endl;
    std::cin >> refundAmount >> std::ws;

    // Checks if refund amount is valid (between 0 and 999,999.00)
    if (refundAmount < 0 || refundAmount > 999999.0) {
        std::cout << "Error: Invalid transfer amount. Amount must be between 0 and 999,999.00." << std::endl;
        std::cout << "Refund cancelled." << std::endl;
        return;
    }

    // Processes refund between users
    setBuyerUsername(buyerUsername);
    setSellerUsername(sellerUsername);
    setRefundAmount(refundAmount);

    // Formats buyer user name to 15 characters
    buyerUsername.resize(15, ' ');

    // Formats seller user name to 15 characters
    sellerUsername.resize(15, ' ');

    // Declares and initializes stringstream
    std::stringstream ss;

    // Formats credit to 9 characters
    ss << std::setfill('0') << std::setw(6) << refundAmount << ".00";
    std::string credit = ss.str();
    ss.str(std::string());  // Clears stringstream

    std::cout << "Refund successful: " << buyerUsername << " " << sellerUsername << " " << credit << std::endl;    

    getFrontend().addToDailyTransaction(this);
}

std::string Refund::getSellerUsername() const {
    return m_sellerUsername;
}

std::string Refund::getBuyerUsername() const {
    return m_buyerUsername;
}

float Refund::getRefundAmount() const {
    return m_refundAmount;
}

void Refund::setSellerUsername(std::string username) {
    m_sellerUsername = username;
}

void Refund::setBuyerUsername(std::string username) {
    m_buyerUsername = username;
}

void Refund::setRefundAmount(float amount) {
    m_refundAmount = amount;
}

// Overrides to string method
std::ostream& operator<<(std::ostream& os, const Refund& obj) {
    // Formats buyer user name to 15 characters
    std::string buyerUsername = obj.getBuyerUsername();
    buyerUsername.resize(15, ' ');

    // Formats seller user name to 15 characters
    std::string sellerUsername = obj.getSellerUsername();
    sellerUsername.resize(15, ' ');

    // Declares and initializes stringstream
    std::stringstream ss;

    // Formats credit to 9 characters
    int creditVal = (int)obj.getRefundAmount();
    ss << std::setfill('0') << std::setw(6) << creditVal << ".00";
    std::string credit = ss.str();
    ss.str(std::string());  // Clears stringstream
        
    return (os << obj.getTransactionCode() << " " << buyerUsername << " " << sellerUsername << " " << credit);
}
