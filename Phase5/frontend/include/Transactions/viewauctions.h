#ifndef VIEWAUCTIONS_H
#define VIEWAUCTIONS_H

#include "transaction.h"

class Frontend;

class ViewAuctions : public Transaction {
public:
    ViewAuctions(Frontend& frontend);
    void processTransaction() override;
};

#endif