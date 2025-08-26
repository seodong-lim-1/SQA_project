#ifndef ITEM_H
#define ITEM_H

#include "../include/Users/user.h"

class Item {
public:
    Item(const std::string& itemName, User* seller, User* topBidder, const int& auctionLengthRemaining, const float& currentHighestBid);
    ~Item();
    
    const std::string& getItemName() const;
    User* getSeller() const;
    User* getTopBidder() const;
    const int& getAuctionLengthRemaining() const;
    const float& getCurrentHighestBid() const;

    friend std::ostream& operator<<(std::ostream& os, const Item& obj);
    
protected:
    std::string m_itemName;
    User* m_seller;
    User* m_topBidder;
    int m_auctionLengthRemaining;
    float m_currentHighestBid;
};

#endif