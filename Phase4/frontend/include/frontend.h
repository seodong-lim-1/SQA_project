#ifndef FRONTEND_H
#define FRONTEND_H

#include "../include/Users/admin.h"
#include "../include/Users/fullstandard.h"
#include "../include/Users/sellstandard.h"
#include "../include/Users/buystandard.h"
#include "../include/item.h"
#include <iomanip>

class Transaction;  // Forward declaration to use Transaction in Frontend

class Frontend  {
public:
    Frontend(std::string filenameAvailableUsers, std::string filenameAvailableItems, std::string filenameDailyTransaction);

    void setCurrentUser(User* user);
    void setAvailableUsers();
    void setAvailableItems();
    void setIsActive(bool isActive);
    void setAllowLogin(bool allowLogin);
    void setAllowLogout(bool allowLogout);
    void addToDailyTransaction(Transaction* transaction);

    User* getCurrentUser() const;
    const std::vector<User*>& getAvailableUsers() const;
    const std::vector<Item*>& getAvailableItems() const;
    std::vector<Transaction*>& getTransactionHistory();
    bool getIsActive() const;
    bool getAllowLogin() const;
    bool getAllowLogout() const;

    void writeDailyTransaction();
    std::string hashString(const std::string& str);

protected:
    User* m_currentUser;
    std::vector<User*> m_availableUsers;
    std::vector<Item*> m_availableItems;
    std::vector<Transaction*> m_transactionHistory;
    bool m_isActive = false;
    bool m_allowLogin = true;
    bool m_allowLogout = false;
    std::string m_filenameAvailableUsers;
    std::string m_filenameAvailableItems;
    std::string m_filenameDailyTransaction;
};

#endif