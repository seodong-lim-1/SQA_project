#include "../include/Transactions/advertise.h"
#include <iostream>
#include <string>
#include <fstream>

void Advertise::processTransaction() 
{
    // TODO put up an item for auction
    // TODO should save this information to the daily transaction file
    // TODO Semi-privileged transaction - only accepted when logged in any type of account except standard-buy.
    // TODOno further transactions should be accepted on a new ticket for sale until the next session.
	
	// check what type of account the user is
	void userType()
	{
		return;
	}
	
	
	// Asks for name of item 
	void userInputItemName{
		string itemName;
		std::cout << "Enter name of item";
		std::cin >> itemName;
		
		//if character is longer than 25
		if(itemName.length()>25)
		{
			std::cout << "Item name invalid as it is over 25 characters" ;
			return;
		}
	}
	
	// Asks for the minimum bid
	void userInputItemBid
	{
		float itemBid;
		std::cout << "Enter the minimum bid (has to be less than 999.99): ";
		std::cin >> itemBid;
		
		// if minimum bid is higher than accepted value, it returns back
		if(itemBid>999.99)
		{
			std::cout << "Invalid bid value, please try again" ;
			return;
		}
	}
	
	// asks for the amount of days it will be listed for (max 100)
	void userInputDayslisted
	{
		int itemDayslisted;
		std::cout << "Enter the amount of days item will be listed for (max 100 days)" ;
		std::cin >> itemDayslisted;
		
		// if user inputs listing day value greater than 100
		if(itemDayslisted>100)
		{
			std::cout << "Amount of days listed value is too large" ;
			return;
		}
	}
	
	
	

}