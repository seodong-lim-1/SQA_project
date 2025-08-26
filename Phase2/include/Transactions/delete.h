#ifndef DELETE_H
#define DELETE_H

#include "transaction.h"
class Delete : public Transaction {
public:
    void processTransaction() override;
};

#endif