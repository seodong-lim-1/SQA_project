#include "../include/Transactions/bid.h"
#include "../include/frontend.h"

// Constructs Bid with a default transaction code of "04"
Bid::Bid(Frontend& frontend) : Transaction(frontend, "04") {}

void Bid::processTransaction() {
    
    //check privilage
    User* currentUser = getFrontend().getCurrentUser();
    if (currentUser->getPrivilege() == "SS") {
        std::cout << "Error: Invalid Transaction. Sellers cannot bid an item." << std::endl;
        return;
    }

    std::cout << "Processing Bid Transaction..." << std::endl;

    //Ask user for item name
    bool itemAvailable = false;
    std::string itemName;
    std::cout << "Enter item name:" << std::endl;
    std::cin >> itemName >> std::ws;

    //check if item is available
    std::vector<Item*> storedItems; //for storing all items that the user is asking for

    std::vector<Item*> m_availableItems = getFrontend().getAvailableItems();
    for (std::vector<Item*>::iterator it = m_availableItems.begin(); it != m_availableItems.end(); ++it) {
        if ((*it)->getItemName() == itemName) {
            storedItems.push_back(*it); //store pointer of Item
            itemAvailable = true;
            break;
        }
    }
    if (!itemAvailable) { //item is found
        std::cout << "Error: Item is not available." << std::endl;    
    }

    
    //ask user for seller
    bool sellerAvailable = false;
    std::string sellerName;
    std::cout << "Enter seller name:" << std::endl;
    std::cin >> sellerName >> std::ws;

    //Find item corrsponding to the seller
    std::vector<Item*> userItemRequest;
    for (std::vector<Item*>::iterator it = storedItems.begin(); it != storedItems.end(); ++it) {
        if ((*it)->getSeller()->getUsername() == sellerName) {
            userItemRequest.push_back(*it); //store pointer of specific Item
            sellerAvailable = true;
            break;
        }
    }
    if (!sellerAvailable) { //seller is found
        std::cout << "Error: Invalid Transaction. Item does not exist." << std::endl;
        return;
    }



    double currentBid = (userItemRequest[0])->getCurrentHighestBid(); //store highest bid amount
    std::cout << "Current highest bid: " << currentBid << std::endl;

    // Ask for new bid amount
    double newBid;
    std::cout << "Enter your bid:" << std::endl;
    std::cin >> newBid >> std::ws;

    if (newBid >= 1000 || newBid < 0){ //if bid is over to equal to 1000 or under 0
        std::cout << "Error: Bid must be between 0 and 999.99 " << std::endl;
        return;
    }
    if (newBid <= currentBid){ //if bid is less or equal to current bid
        std::cout << "Error: Invalid Transaction. Bid is less than previous current highest bid." << std::endl;
        return;
    } 
    else if (newBid <= (currentBid + currentBid*0.05)){ //if bit is not greater than the current bid by +5%
        //User* currentUser = getFrontend().getCurrentUser(); //get user privilage
        if (currentUser->getPrivilege() != "AA") { //check if the user is not an admin
            std::cout << "Error: Invalid Transaction. Bid must be atleast 5"<<"%"<<" higher than previous current highest bid." << std::endl;
            return;
        }
    }
    else{
        //go to the next part
    }

    // Add bid to item object
    Item* editedItem; //  Copy item to a new Item object
    //  Add new highest bid value to old highest bid value
    editedItem = new Item((userItemRequest[0])->getItemName(), (userItemRequest[0])->getSeller(), currentUser, (userItemRequest[0])->getAuctionLengthRemaining(), newBid);
    //  Call Bid item setter to set edited item
    setEditedItem(editedItem);
    
    std::cout << "Bid successful: " << *editedItem << std::endl;
    getFrontend().addToDailyTransaction(this);
}

Item* Bid::getEditedItem() const {
    return m_editedItem;
}

void Bid::setEditedItem(Item* item) {
    m_editedItem = item;
}

// Overrides to string method
std::ostream& operator<<(std::ostream& os, const Bid& obj) {
    const Item* item = obj.getEditedItem();
    
    return (os << obj.getTransactionCode() << " " << *item);
    //return (os << "XX_IIIIIIIIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUUU_DDD_BBBBBB");
}
