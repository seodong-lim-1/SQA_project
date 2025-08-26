#ifndef LOGOUT_H
#define LOGOUT_H

#include "transaction.h"

class Frontend;

class Logout : public Transaction {
public:
    Logout(Frontend& frontend);
    void processTransaction() override;

    friend std::ostream& operator<<(std::ostream& os, const Logout& obj);
};

#endif