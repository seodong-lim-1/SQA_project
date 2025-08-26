#ifndef REFUND_H
#define REFUND_H

#include "transaction.h"

class Frontend;

class Refund : public Transaction {
public:
    Refund(Frontend& frontend);
    void processTransaction() override;

    std::string getSellerUsername() const;
    std::string getBuyerUsername() const;
    float getRefundAmount() const;

    void setSellerUsername(const std::string sellerUsername);
    void setBuyerUsername(const std::string buyerUsername);
    void setRefundAmount(float refundAmount);

    friend std::ostream& operator<<(std::ostream& os, const Refund& obj);
protected:
    std::string m_sellerUsername;
    std::string m_buyerUsername;
    float m_refundAmount;
};

#endif
