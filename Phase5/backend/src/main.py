import sys
from .backend import Backend
from .Transactions.bid import Bid

# checks for invalid arguments
if (len(sys.argv) != 3):
    print("Error: Invalid number of arguments. Expected 2, got " + str(len(sys.argv)-1) + ".")
    print("Usage: ./main.py <available_users_filepath> <available_items_filepath>")
    sys.exit(1)

# initializes backend
available_users_filepath = sys.argv[1]
available_items_filepath = sys.argv[2]  
backend = Backend(available_users_filepath, available_items_filepath)
backend.set_available_users()
backend.set_available_items()
backend.set_merged_daily_transactions()

# processes backend
backend.process()