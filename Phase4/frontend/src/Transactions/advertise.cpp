#include "../include/Transactions/advertise.h"
#include "../include/frontend.h"
#include <iostream>
#include <string>
#include <fstream>

// Constructs Advertise with a default transaction code of "03"
Advertise::Advertise(Frontend& frontend) : Transaction(frontend, "03") {}

void Advertise::processTransaction() {
	std::cout << "Processing Advertise Transaction..." << std::endl;	

	// Checks if the current user is a buyer
	User* currentUser = getFrontend().getCurrentUser();
    if (currentUser->getPrivilege() == "BS") {
        std::cout << "Error: Invalid Transaction. User lacks privilege." << std::endl;
		std::cout << "Advertise cancelled." << std::endl;
        return;
    }
	
	// Asks for name of item 
	std::string itemName;
	std::cout << "Enter item name:" << std::endl;
	std::cin >> itemName >> std::ws;
	
	// Checks if item name is over 25 characters
	if(itemName.length()>25) {
		std::cout << "Error: Invalid Transaction. Item name must be less than 25 characters." << std::endl;
		std::cout << "Advertise cancelled." << std::endl;
		return;
	}
	
	// Asks for the minimum bid
	float minimumBid;
	std::cout << "Enter the minimum bid: " << std::endl;
	std::cin >> minimumBid >> std::ws;
	
	// Checks if bid is greater than 999.99
	if(minimumBid>999.99) {
		std::cout << "Error: Invalid Transaction. Minimum bid must be less than 999.99." << std::endl;
		std::cout << "Advertise cancelled." << std::endl;
		return;
	}
	
	// Gets the amount of days the item will be listed for
	int auctionLength;
	std::cout << "Enter the amount of days item will be listed for:" << std::endl;
	std::cin >> auctionLength >> std::ws;
	
	// Checks if days listed is greater than 100
	if(auctionLength>100) {
		std::cout << "Error: Invalid Transaction. Item can only be listed for 100 days." << std::endl;
		std::cout << "Advertise cancelled." << std::endl;
		return;
	}

	// Creates a new item 
	User *tempBuyer = new User("", "", "", 0.0);
	Item *newItem = new Item(itemName, getFrontend().getCurrentUser(), tempBuyer, auctionLength, minimumBid);
	setNewItem(newItem);

	std::cout << "Advertise successful: " << *newItem << std::endl;

    getFrontend().addToDailyTransaction(this);
}

Item* Advertise::getNewItem() const {
	return m_newItem;
}

void Advertise::setNewItem(Item* item) {
	m_newItem = item;
}

// Overrides to string method
std::ostream& operator<<(std::ostream& os, const Advertise& obj) {
	Item *item = obj.getNewItem();

    // Formats item name to 25 characters
    std::string itemName = item->getItemName();
    itemName.resize(25, ' ');

    // Formats seller name to 15 characters
    std::string sellerName = item->getSeller()->getUsername();
    sellerName.resize(15, ' ');

    // Declares and initializes stringstream
    std::stringstream ss;

    // Formats auction length remaining to 3 characters
    int auctionLengthRemainingVal = (int)item->getAuctionLengthRemaining();
    ss << std::setfill('0') << std::setw(3) << auctionLengthRemainingVal;
    std::string auctionLengthRemaining = ss.str();
    ss.str(std::string());  // Clears stringstream

    // Formats current highest bid to 6 characters
    int currentHighestBidVal = (int)item->getCurrentHighestBid();
    ss << std::setfill('0') << std::setw(3) << currentHighestBidVal << ".00";
    std::string currentHighestBid = ss.str();
    ss.str(std::string());  // Clears stringstream

	return (os << obj.getTransactionCode() << " " << itemName << " " << sellerName << " " << auctionLengthRemaining << " " << currentHighestBid);
}