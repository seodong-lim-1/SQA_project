#ifndef LOGOUT_H
#define LOGOUT_H

#include "transaction.h"
class Logout : public Transaction {
public:
    void processTransaction() override;
};

#endif