#ifndef VIEWUSERS_H
#define VIEWUSERS_H

#include "transaction.h"

class Frontend;

class ViewUsers : public Transaction {
public:
    ViewUsers(Frontend& frontend);
    void processTransaction() override;
};

#endif