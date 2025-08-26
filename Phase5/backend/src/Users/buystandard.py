from .user import User

class BuyStandard(User):
    def __init__(self, username, password, credit):
        super().__init__(username, "BS", password, credit)

    def __str__(self):
        return f"BuyStandard({self.username},{self.privilege},{self.password},{self.credit})"