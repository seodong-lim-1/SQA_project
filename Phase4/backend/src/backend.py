
from typing import List
import glob

from Users.user import User
from Users.admin import Admin
from Users.fullstandard import FullStandard
from Users.buystandard import BuyStandard
from Users.sellstandard import SellStandard

from item import Item

from Transactions.transaction import Transaction
from Transactions.addcredit import AddCredit
from Transactions.advertise import Advertise
from Transactions.bid import Bid
from Transactions.create import Create
from Transactions.delete import Delete
from Transactions.refund import Refund

class Backend:
    def __init__(self, old_users_filepath: str, old_items_filepath: str):
        self.transactions = []
        self.users = []
        self.items = []
        
        self.old_users_filepath = old_users_filepath
        self.old_items_filepath = old_items_filepath

    def __str__(self):
        transactions = "".join([str(transaction) for transaction in self.transactions])
        users = "".join([str(user) for user in self.users])
        items = "".join([str(item) for item in self.items])
        return f"Backend({transactions},{users},{items})"
    
    def find_user(self, username) -> User:
        found_user = [user for user in self.users if user.username  == username][0]
        return found_user
    
    def find_item(self, item_name, seller) -> Item:
        found_item = [item for item in self.items if item.item_name == item_name and item.seller == seller][0]
        return found_item
    
    def set_available_users(self) -> None:
        file = open(self.old_users_filepath, "r")
        
        for line in file:
            # breaks loop if end of file is reached
            if line == "END":
                break
            
            # parses line into tokens
            token = line.split()
            username = token[0]
            privilege = token[1]
            credit = float(token[2])
            password = token[3]
            
            # creates user object based on privilege and adds it to users list
            if privilege == "AA":
                self.users.append(Admin(username, password, credit, ))
            elif privilege == "FS":
                self.users.append(FullStandard(username, password, credit))
            elif privilege == "BS":
                self.users.append(BuyStandard(username, password, credit))
            elif privilege == "SS":
                self.users.append(SellStandard(username, password, credit))
            else:
                pass
        
        file.close()
        
        return None
        
    def set_available_items(self) -> None:
        file = open(self.old_items_filepath, "r")
        
        for line in file:
            # breaks loop if end of file is reached
            if line == "END":
                break
            
            # parses line into tokens
            token = line.split()
            item_name = token[0]
            found_seller = self.find_user(token[1])
            found_top_bidder =  self.find_user(token[2])
            days_left = int(token[3])
            top_bid = float(token[4])
            
            # creates item object and adds it to items list
            item = Item(item_name, found_seller, found_top_bidder, days_left, top_bid)
            self.items.append(item)
            
        file.close()
        
        return None
    
    def set_merged_daily_transactions(self) -> None:
        # merges all daily transaction files into one file
        read_files = glob.glob("../database/Daily_Transactions/*.txt")
        with open("../database/Merged_Daily_Transaction.txt", "wb") as outfile:
            for f in read_files:
                with open(f, "rb") as infile:
                    outfile.write(infile.read())
            outfile.write("00".encode())
        
        # reads in merged daily transaction file
        file = open("../database/Merged_Daily_Transaction.txt", "r")
        for line in file:
            # breaks at end of file
            if line == "00":
                break
            
            # splits line into tokens
            token = line.split()
            transaction_code = token[0]
            
            # creates transaction objects based on transaction code and adds it to transactions list
            if transaction_code == "01":
                privilege = token[2]
                new_user = None
                if privilege == "AA":
                    new_user = Admin(token[1], token[4], float(token[3]))
                elif privilege == "FS":
                    new_user = FullStandard(token[1], token[4], float(token[3]))
                elif privilege == "BS":
                    new_user = BuyStandard(token[1], token[4], float(token[3]))
                elif privilege == "SS":
                    new_user = SellStandard(token[1], token[4], float(token[3]))
                transaction = Create(new_user)
                self.transactions.append(transaction)
            elif transaction_code == "02":
                found_user = self.find_user(token[1])
                transaction = Delete(found_user)
                self.transactions.append(transaction)
            elif transaction_code == "03":
                found_user = self.find_user(token[2])
                item_name = token[1]
                days_left = int(token[3])
                top_bid = float(token[4])
                new_item = Item(item_name, found_user, None, days_left, top_bid)
                transaction = Advertise(new_item)
                self.transactions.append(transaction)
            elif transaction_code == "04":
                found_seller = self.find_user(token[2])
                item_name = token[1]
                found_item = self.find_item(item_name, found_seller)
                found_buyer = self.find_user(token[3])
                new_bid = float(token[5])
                transaction = Bid(found_item, new_bid, found_buyer)
                self.transactions.append(transaction)
            elif transaction_code == "05":
                found_buyer = self.find_user(token[1])
                found_seller = self.find_user(token[2])
                refund_amount = float(token[3])
                transaction = Refund(found_seller, found_buyer, refund_amount)
                self.transactions.append(transaction)
            elif transaction_code == "06":
                found_user = self.find_user(token[1])
                new_credit = float(token[3])
                transaction = AddCredit(found_user, new_credit)
                self.transactions.append(transaction)
                
        file.close()

        return None
    
    def write_new_available_users(self) -> None:
        file = open("../database/New_Current_User_Accounts.txt", "w")
        for user in self.users:
            file.write(f"{user.username.ljust(15)} {user.privilege} {'{:09.2f}'.format(user.credit)} {user.password}\n")
        file.write("END")
        file.close()
        return None
    
    def write_new_available_items(self) -> None:
        file = open("../database/New_Available_Items.txt", "w")
        for item in self.items:
            bidder_name = ''.ljust(15)
            if item.top_bidder is not None:
                bidder_name = item.top_bidder.username.ljust(15)
            file.write(f"{item.item_name.ljust(25)} {item.seller.username.ljust(15)} {bidder_name} {'{:03d}'.format(item.days_left - 1)} {'{:06.2f}'.format(item.top_bid)}\n")
        file.write("END")
        file.close()
        return None