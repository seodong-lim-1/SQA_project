from .transaction import Transaction
from item import Item
from Users.user import User

class Bid(Transaction):
    def __init__(self, item_to_edit: Item, new_bid: float, bidder: User):
        super().__init__("04")
        self.item_to_edit = item_to_edit
        self.new_bid = new_bid
        self.bidder = bidder
    
    def __str__(self):
        return f"Bid({self.item_to_edit},{self.bidder},{self.new_bid})"
    
    def process_transaction(self, backend) -> None:
        # removes item from items list if bidder does not have enough credit
        if self.bidder.credit < self.new_bid:
            backend.items.remove(self.item_to_edit)
        else:
            # decreases bidder's credit by new bid amount
            bidderIndex = backend.users.index(self.bidder)
            backend.users[bidderIndex].credit -= self.new_bid
            
            # updates item with new top bidder info
            itemIndex = backend.items.index(self.item_to_edit)
            backend.items[itemIndex].top_bid = self.new_bid
            backend.items[itemIndex].top_bidder = self.bidder
            backend.items[itemIndex].days_left -= 1
            
        