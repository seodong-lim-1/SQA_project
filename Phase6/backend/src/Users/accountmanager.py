from .user import User

class AccountManager(User):
    def __init__(self, username, password, credit):
        super().__init__(username, "AM", password, credit)

    def __str__(self):
        return f"Admin({self.username},{self.privilege},{self.password},{self.credit})"