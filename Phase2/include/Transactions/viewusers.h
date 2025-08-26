#ifndef VIEWUSERS_H
#define VIEWUSERS_H

#include "transaction.h"
class ViewUsers : public Transaction {
public:
    void processTransaction() override;
};

#endif