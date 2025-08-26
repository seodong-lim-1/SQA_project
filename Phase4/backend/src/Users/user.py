class User:
    def __init__(self, username: str, privilege: str, password: str, credit: float):
        self.username = username
        self.privilege = privilege
        self.password = password
        self.credit = credit
        
    def __str__(self):
        return f"User({self.username},{self.privilege},{self.password},{self.credit})"
    
    def __eq__(self, other):
        # checks if this == other
        return self.username == other.username and self.privilege == other.privilege and self.password == other.password and self.credit == other.credit    