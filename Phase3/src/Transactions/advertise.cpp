#include "../include/Transactions/advertise.h"
#include "../include/frontend.h"
#include <iostream>
#include <string>
#include <fstream>

// Constructs Advertise with a default transaction code of "03"
Advertise::Advertise(Frontend& frontend) : Transaction(frontend, "03") {}

void Advertise::processTransaction() {
    //      Get current user from frontend, if it is buy standard, error
	User* currentUser = getFrontend().getCurrentUser();
    if (currentUser->getPrivilege() == "BS") {
        std::cout << "Error: Invalid Transaction. User is a buy standard account." << std::endl;
        return;
    }
	
	// Asks for name of item 
	std::string itemName;
	std::cout << "Enter name of item" << std::endl;
	std::cin >> itemName >> std::ws;
	
	// Checks if item name is over 25 characters
	if(itemName.length()>25) {
		std::cout << "Item name invalid as it is over 25 characters" << std::endl;
		return;
	}
	
	// Asks for the minimum bid
	float itemBid;
	std::cout << "Enter the minimum bid (has to be less than 999.99): " << std::endl;
	std::cin >> itemBid >> std::ws;
	
	// Checks if bid is greater than 999.99
	if(itemBid>999.99) {
		std::cout << "Invalid bid value, please try again" << std::endl;
		return;
	}
	
	// Asks for the amount of days the item will be listed for
	int itemDayslisted;
	std::cout << "Enter the amount of days item will be listed for (max 100 days)" << std::endl;
	std::cin >> itemDayslisted >> std::ws;
	
	// Checks if days listed is greater than 100
	if(itemDayslisted>100) {
		std::cout << "Amount of days listed value is too large" << std::endl;
		return;
	}

	// TODO Create a new item object
	//		Call Item constructor with the following parameters:
	//			itemName
	//			getFrontend().getCurrentUser()
	//			nullptr
	//			itemDayslisted
	//			itemBid
	
	// TODO Add item to Advertise object
	//		Call Advertise setter to set new item

    getFrontend().addToDailyTransaction(this);
}

// Overrides to string method
std::ostream& operator<<(std::ostream& os, const Advertise& obj) {
	// TODO implement to fit regex
	return (os << "XX_IIIIIIIIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_DDD_BBBBBB");
}