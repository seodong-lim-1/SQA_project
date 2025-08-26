from .transaction import Transaction
from item import Item

class Advertise(Transaction):
    def __init__(self, new_item: Item):
        super().__init__("03")
        self.new_item = new_item
        
    def __str__(self):
        return f"Advertise({self.new_item})"
    
    def process_transaction(self, backend) -> None:
        backend.items.append(self.new_item)
    
