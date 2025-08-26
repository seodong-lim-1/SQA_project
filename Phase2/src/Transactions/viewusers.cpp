#include "../include/Transactions/viewusers.h"
#include "../include/frontend.h"
#include <iostream>

void ViewUsers::processTransaction()
{
	// print the current users
	std::cout << readCurrentUsers() << std::endl;
	
}
