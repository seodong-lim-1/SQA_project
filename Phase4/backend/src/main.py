import sys
from backend import Backend
from Transactions.bid import Bid

# checks for invalid arguments
if (len(sys.argv) != 3):
    print("Error: Invalid number of arguments. Expected 2, got " + str(len(sys.argv)-1) + ".")
    print("Usage: ./main.py <available_users_filepath> <available_items_filepath>")
    sys.exit(1)

# initializes backend
backend = Backend(sys.argv[1], sys.argv[2])
backend.set_available_users()
backend.set_available_items()
backend.set_merged_daily_transactions()

# gets highest bids
highest_bids = {}
for transaction in backend.transactions:
    if isinstance(transaction, Bid):
        key = (transaction.transaction_code, transaction.item_to_edit)
        if key not in highest_bids or transaction.new_bid > highest_bids[key].new_bid:
            highest_bids[key] = transaction

# filters out transactions that have lower bids than the highest bids
backend.transactions = [transaction for transaction in backend.transactions if not isinstance(transaction, Bid) or transaction in highest_bids.values()]

# processes transactions
for transaction in backend.transactions:
    print("Processing transaction: " + str(transaction))
    try:
        transaction.process_transaction(backend)
    except Exception as e:
        print(f"ERROR: {transaction}: {e}")

# writes new available users and items files
backend.write_new_available_users()
backend.write_new_available_items()