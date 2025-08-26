from .transaction import Transaction
from ..Users.user import User

class AddCredit(Transaction):
    def __init__(self, user_to_edit: User, new_credit: float):
        super().__init__("06")
        self.user_to_edit = user_to_edit
        self.new_credit = new_credit
        
    def __str__(self):
        return f"AddCredit({self.user_to_edit},{self.new_credit})"

    def process_transaction(self, backend) -> None:
        user_to_edit_index = backend.users.index(self.user_to_edit) 
        backend.users[user_to_edit_index].credit = self.new_credit