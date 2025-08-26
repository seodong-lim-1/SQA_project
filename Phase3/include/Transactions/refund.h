#ifndef REFUND_H
#define REFUND_H

#include "transaction.h"

class Frontend;

class Refund : public Transaction {
public:
    Refund(Frontend& frontend);
    void processTransaction() override;

    friend std::ostream& operator<<(std::ostream& os, const Refund& obj);

    // TODO get edited buyer
    // TODO set edited buyer

    // TODO get edited seller
    // TODO set edited seller

protected:
    // TODO Consider removing these, as they could be redundant based off pseudocode in refund.cpp
    // std::string buyerUsername;
    // std::string sellerUsername;
    // double transferAmount;
    // bool validateUsers(); // checks if buyer and seller are current users

    // TODO initialize edited buyer with pattern m_<variableName>
    // TODO initialize edited seller with pattern m_<variableName>
};

#endif
