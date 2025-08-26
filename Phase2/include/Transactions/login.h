#ifndef LOGIN_H
#define LOGIN_H

#include "transaction.h"
class Login : public Transaction {
public:
    std::fstream* availableUsers;
    std::string username;
    bool acceptanceFlag = false;

    void processTransaction() override;
    bool startFrontend();
};


#endif