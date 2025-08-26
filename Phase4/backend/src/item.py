from Users.user import User

class Item:
    def __init__(self, item_name: str, seller: User, top_bidder: User, days_left: int, top_bid: float):
        self.item_name = item_name
        self.seller = seller
        self.top_bidder = top_bidder
        self.days_left = days_left
        self.top_bid = top_bid
        
    def __hash__(self) -> int:
        return hash(self.item_name)

    def __str__(self):
        return f"Item({self.item_name},{self.seller},{self.top_bidder},{self.days_left},{self.top_bid})"
    
    def __eq__(self, other):
        return self.item_name == other.item_name and self.seller == other.seller and self.top_bidder == other.top_bidder and self.days_left == other.days_left and self.top_bid == other.top_bid
    