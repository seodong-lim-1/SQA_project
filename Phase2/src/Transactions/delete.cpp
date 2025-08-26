#include "../include/Transactions/delete.h"
#include "user.h"

void Delete::processTransaction() 
{
    // TODO cancel any outstanding items for sale and remove the user account.
    // TODO should save this information for the daily transaction file
    // TODO privileged transaction - only accepted when logged in as admin user
    // TODO username must be the name of an existing user but not the name of the current user
    // TODO no further transactions should be accepted on a deleted user’s available inventory of items for sale.
	
	// Input username
	void usernameInput()
	{
		string username;
		std::cout << "Input username" ; 
		std::cin >> username;
	}
	
	// Check if user is an admin
	void userAdminCheck()
	{
		return;
	}
	
	
	

}
