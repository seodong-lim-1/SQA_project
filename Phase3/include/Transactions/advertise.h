#ifndef ADVERTISE_H
#define ADVERTISE_H

#include "transaction.h"

class Frontend;

class Advertise : public Transaction {
public:
    Advertise(Frontend& frontend);
    void processTransaction() override;

    friend std::ostream& operator<<(std::ostream& os, const Advertise& obj);

    // TODO get new item
    // TODO set new item
protected:
    // TODO initialize new item with pattern m_<variableName>
};

#endif