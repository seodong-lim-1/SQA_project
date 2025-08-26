from .transaction import Transaction
from ..item import Item
from ..Users.user import User

class Bid(Transaction):
    def __init__(self, item_to_edit: Item, new_bid: float, bidder: User):
        super().__init__("04")
        self.item_to_edit = item_to_edit
        self.new_bid = new_bid
        self.bidder = bidder
    
    def __str__(self):
        return f"Bid({self.item_to_edit},{self.bidder},{self.new_bid})"
    
    def process_transaction(self, backend) -> None:
        # checks if new bid is valid
        if self.new_bid <= self.item_to_edit.top_bid:
            raise Exception("Bid must be greater than current top bid.")    
        
        # updates item with new top bidder info
        itemIndex = backend.items.index(self.item_to_edit)
        backend.items[itemIndex].top_bid = self.new_bid
        backend.items[itemIndex].top_bidder = self.bidder
        backend.items[itemIndex].days_left -= 1
        
        # processes bidder won item
        if backend.items[itemIndex].days_left == 0:
            backend.items.remove(self.item_to_edit)
            
            # if bidder doesnt have enough funds, cancels transaction
            if self.bidder.credit < self.new_bid:
                raise Exception("Bidder does not have enough funds to complete transaction.")
            
            self.bidder.credit -= self.new_bid
            self.item_to_edit.seller.credit += self.new_bid
            
        