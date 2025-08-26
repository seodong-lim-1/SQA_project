from .transaction import Transaction
from ..Users.user import User

class Refund(Transaction):
    def __init__(self, seller: User, buyer: User, refund_amount: float):
        super().__init__("05")
        self.seller = seller
        self.buyer = buyer
        self.refund_amount = refund_amount
        
    def __str__(self):
        return f"Refund({self.seller},{self.buyer},{self.refund_amount})"
        
    def process_transaction(self, backend) -> None:
        seller_index = backend.users.index(self.seller) 
        buyer_index = backend.users.index(self.buyer)
        backend.users[seller_index].credit -= self.refund_amount
        backend.users[buyer_index].credit += self.refund_amount