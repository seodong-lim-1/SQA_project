#include "../include/item.h"

Item::Item(const std::string& itemName, User* seller, User* topBidder, const int& auctionLengthRemaining, const float& currentHighestBid) {
    m_itemName = itemName;
    m_seller = seller;
    m_topBidder = topBidder;
    m_auctionLengthRemaining = auctionLengthRemaining;
    m_currentHighestBid = currentHighestBid;
}

Item::~Item(){
    delete m_seller;
    delete m_topBidder;
}

const std::string& Item::getItemName() const {
    return m_itemName;
}

User* Item::getSeller() const {
    return m_seller;
}

User* Item::getTopBidder() const {
    return m_topBidder;
}

const int& Item::getAuctionLengthRemaining() const {
    return m_auctionLengthRemaining;
}

const float& Item::getCurrentHighestBid() const {
    return m_currentHighestBid;
}

// Overrides to string method
std::ostream& operator<<(std::ostream& os, const Item& obj) {
    // Formats item name to 25 characters
    std::string itemName = obj.getItemName();
    itemName.resize(25, ' ');

    // Formats seller name to 15 characters
    std::string sellerName = obj.getSeller()->getUsername();
    sellerName.resize(15, ' ');

    // Formats top bidder name to 15 characters
    std::string topBidderName = obj.getTopBidder()->getUsername();
    topBidderName.resize(15, ' ');

    // Declares and initializes stringstream
    std::stringstream ss;

    // Formats auction length remaining to 3 characters
    int auctionLengthRemainngVal = (int)obj.getAuctionLengthRemaining();
    ss << std::setfill('0') << std::setw(3) << auctionLengthRemainngVal;
    std::string auctionLengthRemaining = ss.str();
    ss.str(std::string());  // Clears stringstream

    // Formats current highest bid to 6 characters
    int currentHighestBidVal = (int)obj.getCurrentHighestBid();
    ss << std::setfill('0') << std::setw(3) << currentHighestBidVal << ".00";
    std::string currentHighestBid = ss.str();
    ss.str(std::string());  // Clears stringstream
    
    return (os << itemName << " " << sellerName << " " << topBidderName << " " << auctionLengthRemaining << " " << currentHighestBid);
}