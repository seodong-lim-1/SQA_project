class Transaction:
    def __init__(self, transaction_code: str):
        self.transaction_code = transaction_code
        
    def __str__(self):
        return f"Transaction({self.transaction_code})"
    