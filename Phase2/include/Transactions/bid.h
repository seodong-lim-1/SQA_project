#ifndef BID_H
#define BID_H

#include "transaction.h"
class Bid : public Transaction {
public:
    void processTransaction() override;
};

#endif