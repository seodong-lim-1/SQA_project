from .transaction import Transaction
from Users.user import User

class Create(Transaction):
    def __init__(self, new_user: User):
        super().__init__("01")
        self.new_user = new_user
        
    def __str__(self):
        return f"Create({self.new_user})"
    
    def process_transaction(self, backend) -> None:
        backend.users.append(self.new_user)