#ifndef CREATE_H
#define CREATE_H

#include "transaction.h"
class Create : public Transaction {
public:
    void processTransaction() override;
};

#endif