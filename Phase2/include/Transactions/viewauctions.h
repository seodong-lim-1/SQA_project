#ifndef VIEWAUCTIONS_H
#define VIEWAUCTIONS_H

#include "transaction.h"
class ViewAuctions : public Transaction {
public:
    void processTransaction() override;
};

#endif