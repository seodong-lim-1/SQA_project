from .Users.user import User

class Item:
    def __init__(self, item_name: str, seller: User, top_bidder: User, days_left: int, top_bid: float):
        # checks if item name length is valid
        if len(item_name) < 1 or len(item_name) > 25:
            raise ValueError("Item name must be between 1 and 25 characters.")
        
        # checks if top bid is valid
        if top_bid < 0 or top_bid > 999.99:
            raise ValueError("Top bid must be between 0 and 999.99.")
        
        # checks if days left is valid
        if days_left < 1 or days_left > 100:
            raise ValueError("Days left must be between 1 and 100.")
        
        # checks that seller is valid
        if not isinstance(seller, User):
            raise ValueError("Seller must be a valid User instance.")
        
        # checks that top bidder is valid
        if top_bidder is not None and not isinstance(top_bidder, User):
            raise ValueError("Top bidder must be either a User instance or None.")
        
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
    