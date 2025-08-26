#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "../include/Users/user.h"

class Frontend; // Forward declaration to use Frontend in Transactions

class Transaction {
public:
    Transaction(Frontend& frontend, const std::string& transactionCode);
    virtual void processTransaction() = 0;

    Frontend& getFrontend() const;
    std::string getTransactionCode() const;

private:
    Frontend& m_frontend;
    std::string m_transactionCode;
};

#endif