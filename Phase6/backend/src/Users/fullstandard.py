from .user import User

class FullStandard(User):
    def __init__(self, username, password, credit):
        super().__init__(username, "FS", password, credit)
        
    def __str__(self):
        return f"FullStandard({self.username},{self.privilege},{self.password},{self.credit})"
