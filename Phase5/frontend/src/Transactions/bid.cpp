#include "../include/Transactions/bid.h"
#include "../include/frontend.h"

// Constructs Bid with a default transaction code of "04"
Bid::Bid(Frontend& frontend) : Transaction(frontend, "04") {}

void Bid::processTransaction() {
    std::cout << "Processing Bid Transaction..." << std::endl;
    
    // Checks if the current user is a seller
    User* currentUser = getFrontend().getCurrentUser();
    if (currentUser->getPrivilege() == "SS") {
        std::cout << "Error: Invalid Transaction. User lacks privilege." << std::endl;
		std::cout << "Bid cancelled." << std::endl;
        return;
    }

    // Asks for item name
    std::string itemName;
    std::cout << "Enter item name:" << std::endl;
    std::cin >> itemName >> std::ws;

    // Asks for seller name
    std::string sellerName;
    std::cout << "Enter seller name:" << std::endl;
    std::cin >> sellerName >> std::ws;

    // Checks if item exists where item name and seller name match
    Item* foundItem;
    bool itemFound = false;
    for (Item* item : getFrontend().getAvailableItems()) {
        if (item->getItemName() == itemName && item->getSeller()->getUsername() == sellerName) {
            foundItem = item;
            itemFound = true;
            break;
        }
    }
    if (!itemFound) {
        std::cout << "Error: Invalid Transaction. Item does not exist." << std::endl;
		std::cout << "Bid cancelled." << std::endl;
        return;
    }

    std::cout << "Current highest bid: " << foundItem->getCurrentHighestBid() << std::endl;

    // Ask for new bid amount
    double newBid;
    std::cout << "Enter new bid:" << std::endl;
    std::cin >> newBid >> std::ws;

    // Checks if bid is valid (between 0 and 999.99):
    if (newBid < 0 || newBid > 999.99) {
        std::cout << "Error: Invalid Transaction. Bid must be between $0.00 and $999.99." << std::endl;
		std::cout << "Bid cancelled." << std::endl;
        return;
    }


    // Checks if bid is greater than current highest bid:
    if (newBid <= foundItem->getCurrentHighestBid()) {
        std::cout << "Error: Invalid Transaction. Bid must be greater than current highest bid." << std::endl;
		std::cout << "Bid cancelled." << std::endl;
        return;
    } else {
        // Checks if user can bypass 5% rule:
        if (currentUser->getPrivilege() != "AA") {
            // Checks if bid is greater than current highest bid by 5%:
            if (newBid <= (foundItem->getCurrentHighestBid() * 1.05)) {
                std::cout << "Error: Invalid Transaction. Bid must be greater than current highest bid by 5%." << std::endl;
                std::cout << "Bid cancelled." << std::endl;
                return;
            }
        }
    }

    // Create edited new item with new bid
    Item* editedItem = new Item(foundItem->getItemName(), foundItem->getSeller(), currentUser, foundItem->getAuctionLengthRemaining(), newBid);
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
}
