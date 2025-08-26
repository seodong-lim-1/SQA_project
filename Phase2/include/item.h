#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    std::string itemName = "";
    std::string sellerName = "";
    std::string topBidderName = "";
    int auctionLengthRemaining = 0;
    float currentHighestBid = 0.0;
};

#endif