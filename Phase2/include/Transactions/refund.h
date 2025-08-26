#ifndef REFUND_H
#define REFUND_H

#include "transaction.h"
class Refund : public Transaction {
public:
    void processTransaction() override;
};

#endif