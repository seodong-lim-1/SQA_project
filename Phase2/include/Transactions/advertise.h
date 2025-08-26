#ifndef ADVERTISE_H
#define ADVERTISE_H

#include "transaction.h"
class Advertise : public Transaction {
public:
    void processTransaction() override;
};

#endif