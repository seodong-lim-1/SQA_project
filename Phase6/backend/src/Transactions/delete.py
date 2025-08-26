from .transaction import Transaction
from ..Users.user import User

class Delete(Transaction):
    def __init__(self, old_user: User):
        super().__init__("02")
        self.old_user = old_user
        
    def __str__(self):
        return f"Delete({self.old_user})"
    
    def process_transaction(self, backend) -> None:
        backend.users.remove(self.old_user)
        # remove all items that were made by the deleted user
        for item in backend.items:
            if (item.seller == self.old_user):
                backend.items.remove(item)
        