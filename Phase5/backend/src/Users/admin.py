from .user import User

class Admin(User):
    def __init__(self, username, password, credit):
        super().__init__(username, "AA", password, credit)

    def __str__(self):
        return f"Admin({self.username},{self.privilege},{self.password},{self.credit})"