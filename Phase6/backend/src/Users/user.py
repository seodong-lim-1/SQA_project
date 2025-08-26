class User:
    def __init__(self, username: str, privilege: str, password: str, credit: float):
        # checks if username length is valid
        if len(username) < 1 or len(username) > 15:
            raise ValueError("Username must be between 1 and 15 characters.")
        
        # checks if password length is valid
        if len(password) < 1:
            raise ValueError("Password must not be empty.")
        
        # checks if credit amount is valid
        if credit < 0 or credit > 999999.99:
            raise ValueError("Credit must be between 0 and 999999.99.")
        
        self.username = username
        self.privilege = privilege
        self.password = password
        self.credit = credit
        
    def __str__(self):
        return f"User({self.username},{self.privilege},{self.password},{self.credit})"
    
    def __eq__(self, other):
        # checks if this == other
        return self.username == other.username and self.privilege == other.privilege and self.password == other.password and self.credit == other.credit    