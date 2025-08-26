#include "../include/frontend.h"
#include "../include/Transactions/transaction.h"
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
#include <filesystem>

Frontend::Frontend(std::string filenameAvailableUsers, std::string filenameAvailableItems, std::string filenameDailyTransaction) {
    m_filenameAvailableUsers = filenameAvailableUsers;
    m_filenameAvailableItems = filenameAvailableItems;
    m_filenameDailyTransaction = filenameDailyTransaction;
}

// Utility function to split a string by whitespace
std::vector<std::string> splitStringByWhitespace(const std::string& str) {
    std::istringstream iss(str);
    std::vector<std::string> tokens;
    std::string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

void Frontend::setCurrentUser(User* user) {
    m_currentUser = user;
}

void Frontend::setAvailableUsers() {
    std::vector<User*> users;
    std::fstream* file = new std::fstream;
    file->open(std::filesystem::current_path()/m_filenameAvailableUsers, std::ios::in | std::ios::out | std::ios::app);
    std::string line;

    // Reads each line of the file
    while (std::getline(*file, line)) {
        // Declares fields
        std::string username, privilege, password;
        float credit;

        // Parses lines into fields
        std::vector<std::string> tokens = splitStringByWhitespace(line);
        if (tokens[0] == "END") break;  // Stops reading file if END is reached
        username = tokens[0];
        privilege = tokens[1];
        credit = std::stof(tokens[2]);
        password = tokens[3];

        // Creates User object based on privilege field
        User* user;
        if (privilege == "AA") {
            user = new Admin(username, password, credit);
        } else if (privilege == "FS") {
            user = new FullStandard(username, password, credit);
        } else if (privilege == "SS") {
            user = new SellStandard(username, password, credit);
        } else if (privilege == "BS") {
            user = new BuyStandard(username, password, credit);
        }

        users.push_back(user);
    }

    file->close();
    m_availableUsers = users;
}

void Frontend::setAvailableItems() {
    std::vector<Item*> items;
    std::fstream* file = new std::fstream;
    file->open(std::filesystem::current_path()/m_filenameAvailableItems, std::ios::in | std::ios::out | std::ios::app);
    std::string line;
    
    // Reads each line of the file
    while (std::getline(*file, line)) {
        // Declares fields
        std::string itemName, sellerName, topBidderName;
        int auctionLengthRemaining;
        float currentHighestBid;

        // Parses lines into fields
        std::vector<std::string> tokens = splitStringByWhitespace(line);
        if (tokens[0] == "END") break;  // Stops reading file if END is reached
        itemName = tokens[0];
        sellerName = tokens[1];
        topBidderName = tokens[2];
        auctionLengthRemaining = std::stoi(tokens[3]);
        currentHighestBid = std::stof(tokens[4]);

        // Finds User object where username matches sellerName
        User* seller;
        for (User* user : m_availableUsers) {
            if (user->getUsername() == sellerName) {
                seller = user;
                break;
            }
        }

        // Finds User object where username matches topBidderName
        User* topBidder;
        for (User* user : m_availableUsers) {
            if (user->getUsername() == topBidderName) {
                topBidder = user;
                break;
            }
        }

        Item* item = new Item(itemName, seller, topBidder, auctionLengthRemaining, currentHighestBid);
        items.push_back(item);
    }

    file->close();
    m_availableItems = items;
}

void Frontend::setIsActive(bool isStarted) {
    m_isActive = isStarted;
}

void Frontend::addToDailyTransaction(Transaction* transaction) {
    m_transactionHistory.push_back(transaction);

    // // For Debugging
    // std::cout << "Transaction history:" << std::endl;
    // for (Transaction* transaction : m_transactionHistory) {
    //     std::cout << transaction->getTransactionCode() << std::endl;
    // }
}

User* Frontend::getCurrentUser() const {
    return m_currentUser;
}

const std::vector<User*>& Frontend::getAvailableUsers() const {
    return m_availableUsers;
}

const std::vector<Item*>& Frontend::getAvailableItems() const {
    return m_availableItems;
}

std::vector<Transaction*>& Frontend::getTransactionHistory() {
    return m_transactionHistory;
}

bool Frontend::getIsActive() const {
    return m_isActive;
}

void Frontend::writeDailyTransaction() {
    std::fstream* file = new std::fstream;
        file->open(std::filesystem::current_path()/m_filenameDailyTransaction, std::ios::in | std::ios::out | std::ios::trunc);

    // Transaction code constants
    const std::string LOGOUT = "00";
    const std::string CREATE = "01";
    const std::string DELETE = "02";
    const std::string ADVERTISE = "03";   
    const std::string BID = "04"; 
    const std::string REFUND = "05";
    const std::string ADDCREDIT = "06";

    // Writes each transaction to file
    std::vector<Transaction*> transactions = getTransactionHistory();

    std::stringstream ss;
    for (auto it = transactions.begin(); it != transactions.end(); ++it) {
        Transaction* transaction = *it;
        std::string transactionCode = transaction->getTransactionCode();

        if (transactionCode == LOGOUT) {
            // XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC_PPPPPPPPPPPPPPPPPPPPPPPPP
            Logout* logoutTransaction = dynamic_cast<Logout*>(transaction);
            ss << *logoutTransaction << std::endl;
        }
        else if (transactionCode == CREATE) {
            // XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC_PPPPPPPPPPPPPPPPPPPPPPPPP
            Create* createTransaction = dynamic_cast<Create*>(transaction);
            ss << *createTransaction << std::endl;
        }
        else if (transactionCode == DELETE) {
            // XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC_PPPPPPPPPPPPPPPPPPPPPPPPP
            Delete* deleteTransaction = dynamic_cast<Delete*>(transaction);
            ss << *deleteTransaction << std::endl;
        }
        else if (transactionCode == ADVERTISE) {
            // XX_IIIIIIIIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_DDD_BBBBBB
            Advertise* advertiseTransaction = dynamic_cast<Advertise*>(transaction);    
            ss << *advertiseTransaction << std::endl;   
        }
        else if (transactionCode == BID) {
            // XX_IIIIIIIIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUUU_DDD_BBBBBB
            Bid* bidTransaction = dynamic_cast<Bid*>(transaction);
            ss << *bidTransaction << std::endl; 
        }
        else if (transactionCode == REFUND) {
            // XX_UUUUUUUUUUUUUUU_SSSSSSSSSSSSSSS_CCCCCCCCC
            Refund* refundTransaction = dynamic_cast<Refund*>(transaction);
            ss << *refundTransaction << std::endl;  
        }
        else if (transactionCode == ADDCREDIT) {
            // XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC_PPPPPPPPPPPPPPPPPPPPPPPPP
            AddCredit* addCreditTransaction = dynamic_cast<AddCredit*>(transaction);
            ss << *addCreditTransaction << std::endl;
        }
    }
    *file << ss.str();

    file->close();
    m_transactionHistory.clear();
}

void Frontend::setAllowLogin(bool allowLogin) {
    m_allowLogin = allowLogin;
}

bool Frontend::getAllowLogin() const {
    return m_allowLogin;
}

void Frontend::setAllowLogout(bool allowLogout) {
    m_allowLogout = allowLogout;
}

bool Frontend::getAllowLogout() const {
    return m_allowLogout;
}

// Utility function that hashes a string
std::string Frontend::hashString(const std::string& str) {
    std::hash<std::string> hash_fn;
    return std::to_string(hash_fn(str));
}