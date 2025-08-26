#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
public:
    virtual void processTransaction() = 0;
};

#endif