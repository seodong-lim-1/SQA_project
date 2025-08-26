#include "../include/Transactions/viewauctions.h"
#include "../include/frontend.h"

// Constructs ViewAuctions with no transaction code
ViewAuctions::ViewAuctions(Frontend& frontend) : Transaction(frontend, "") {}

void ViewAuctions::processTransaction() {
    std::cout << "Processing ViewAuctions Transaction..." << std::endl;

    // Gets all available items
    const std::vector<Item*>& items = getFrontend().getAvailableItems();

    // Prints out all items  
    std::cout << "|-----------------------------------------------------------------------------------------|" << std::endl;
    std::cout << "| Item Name                 | Seller          | Top Bidder      | Days Left | Highest Bid |" << std::endl;
    std::cout << "|-----------------------------------------------------------------------------------------|" << std::endl;
    for (Item* item : items) {
        std::cout << "| " <<  std::left << std::setw(25) << item->getItemName() << " | ";
        std::cout << std::left << std::setw(15) << item->getSeller()->getUsername() << " | ";
        std::cout << std::left << std::setw(15) << item->getTopBidder()->getUsername() << " | ";
        std::cout << std::left << std::setw(9) << item->getAuctionLengthRemaining() << " | ";
        std::cout << std::left << std::setw(11) << std::fixed << std::setprecision(2) << item->getCurrentHighestBid() << " | " << std::endl;
    }
    std::cout << "|-----------------------------------------------------------------------------------------|" << std::endl;
}
