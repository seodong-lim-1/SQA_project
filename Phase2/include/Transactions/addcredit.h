#ifndef ADDCREDIT_H
#define ADDCREDIT_H

#include "transaction.h"
class AddCredit : public Transaction {
public:
    void processTransaction() override;
};

#endif