from .user import User

class SellStandard(User):
    def __init__(self, username, password, credit):
        super().__init__(username, "SS", password, credit)

    def __str__(self):
        return f"SellStandard({self.username},{self.privilege},{self.password},{self.credit})"