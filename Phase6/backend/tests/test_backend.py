import pytest
import tempfile
from ..src.backend import Backend
from ..src.item import Item
from ..src.Users.user import User
from ..src.Users.admin import Admin
from ..src.Users.fullstandard import FullStandard
from ..src.Users.buystandard import BuyStandard
from ..src.Users.sellstandard import SellStandard
from ..src.Transactions.addcredit import AddCredit
from ..src.Transactions.advertise import Advertise
from ..src.Transactions.bid import Bid
from ..src.Transactions.create import Create
from ..src.Transactions.delete import Delete
from ..src.Transactions.refund import Refund

@pytest.fixture
def backend():
    with tempfile.NamedTemporaryFile() as old_users_tempfile, tempfile.NamedTemporaryFile() as old_items_tempfile:
        return Backend(old_users_tempfile.name, old_items_tempfile.name)

def test_create_non_existing_user_succeeds(backend):
    mock_new_user = FullStandard("testuser1", "password", 0)
    create_transaction = Create(mock_new_user)
    create_transaction.process_transaction(backend)
    assert mock_new_user in backend.users
    
def test_create_existing_user_fails(backend):
    mock_existing_user = FullStandard("testuser1", "password", 0)
    backend.users.append(mock_existing_user)
    create_transaction = Create(mock_existing_user)
    with pytest.raises(Exception):
        create_transaction.process_transaction(backend)

def test_delete_existing_user_succeeds(backend):
    mock_existing_user = FullStandard("testuser1", "password", 0)
    backend.users.append(mock_existing_user)
    delete_transaction = Delete(mock_existing_user)
    delete_transaction.process_transaction(backend)
    assert mock_existing_user not in backend.users
    
def test_delete_non_existing_user_fails(backend):
    mock_non_existing_user = FullStandard("testuser1", "password", 0)
    delete_transaction = Delete(mock_non_existing_user)
    with pytest.raises(Exception):
        delete_transaction.process_transaction(backend)

def test_delete_items_owned_by_deleted_user_are_deleted(backend):
    mock_seller = SellStandard("testuser1", "password", 0)
    backend.users.append(mock_seller)
    mock_existing_item = Item("testitem1", mock_seller, None, 1, 0)
    backend.items.append(mock_existing_item)
    delete_transaction = Delete(mock_seller)
    delete_transaction.process_transaction(backend)
    assert mock_existing_item not in backend.items

def test_addcredit_to_existing_user_succeeds(backend):
    mock_existing_user = FullStandard("testuser1", "password", 0)
    backend.users.append(mock_existing_user)
    addcredit_transaction = AddCredit(mock_existing_user,100)
    addcredit_transaction.process_transaction(backend)
    index_user = backend.users.index(mock_existing_user) 
    assert backend.users[index_user].credit == 100
    
def test_addcredit_to_deleted_user_fails(backend):
    mock_deleted_user = FullStandard("testuser1", "password", 0)
    backend.users.append(mock_deleted_user)
    delete_transaction = Delete(mock_deleted_user)
    delete_transaction.process_transaction(backend)
    addcredit_transaction = AddCredit(mock_deleted_user,100)
    with pytest.raises(Exception):
        addcredit_transaction.process_transaction(backend)

def test_advertise_item_succeeds(backend):
    mock_existing_seller = SellStandard("testuser1", "password", 100)
    backend.users.append(mock_existing_seller)
    mock_item = Item("testitem1",mock_existing_seller,None,10,500)
    advertise_transaction = Advertise(mock_item)
    advertise_transaction.process_transaction(backend)
    assert mock_item in backend.items

def test_advertise_item_from_deleted_user_fails(backend):
    mock_existing_seller = SellStandard("testuser1", "password", 100)
    backend.users.append(mock_existing_seller)
    delete_transaction = Delete(mock_existing_seller)
    delete_transaction.process_transaction(backend)
    mock_item = Item("testitem1",mock_existing_seller,None,10,500)
    advertise_transaction = Advertise(mock_item)
    with pytest.raises(Exception):
        advertise_transaction.process_transaction(backend)

def test_bid_succeeds(backend):
    mock_existing_seller = SellStandard("testuser1", "password", 100)
    mock_existing_bidder = BuyStandard("testuser2", "password", 60)
    backend.users.extend([mock_existing_seller, mock_existing_bidder])
    mock_item = Item("testitem1", mock_existing_seller, mock_existing_bidder, 10, 10)
    backend.items.append(mock_item)
    bid_transaction = Bid(mock_item,50,mock_existing_bidder)
    bid_transaction.process_transaction(backend)
    itemIndex = backend.items.index(mock_item)
    assert backend.items[itemIndex].top_bid == 50
    assert backend.items[itemIndex].top_bidder == mock_existing_bidder
    
def test_bid_bidder_credit_decreases_on_last_day(backend):
    mock_existing_seller = SellStandard("testuser1", "password", 100)
    mock_existing_bidder = BuyStandard("testuser2", "password", 60)
    backend.users.extend([mock_existing_seller, mock_existing_bidder])
    mock_item = Item("testitem1", mock_existing_seller, None, 1, 10)
    backend.items.append(mock_item)
    bid_transaction = Bid(mock_item,50,mock_existing_bidder)
    bid_transaction.process_transaction(backend)
    bidder_index = backend.users.index(mock_existing_bidder)
    seller_index = backend.users.index(mock_existing_seller)
    assert backend.users[bidder_index].credit == 10
    assert backend.users[seller_index].credit == 150

def test_bid_bidder_credit_doesnt_decrease_on_not_last_day(backend):
    mock_existing_seller = SellStandard("testuser1", "password", 100)
    mock_existing_bidder = BuyStandard("testuser2", "password", 60)
    backend.users.extend([mock_existing_seller, mock_existing_bidder])
    mock_item = Item("testitem1", mock_existing_seller, None, 2, 10)
    backend.items.append(mock_item)
    bid_transaction = Bid(mock_item,50,mock_existing_bidder)
    bid_transaction.process_transaction(backend)
    bidder_index = backend.users.index(mock_existing_bidder)
    seller_index = backend.users.index(mock_existing_seller)
    item_index = backend.items.index(mock_item)
    assert backend.users[bidder_index].credit == 60
    assert backend.users[seller_index].credit == 100
    assert backend.items[item_index].top_bid == 50

def test_bid_only_highest_bid_accepted(backend):
    mock_existing_seller = SellStandard("testuser1", "password", 100)    
    mock_existing_bidder1 = BuyStandard("testuser2", "password", 100)
    mock_existing_bidder2 = BuyStandard("testuser3", "password", 200)
    mock_existing_bidder3 = BuyStandard("testuser4", "password", 300)
    backend.users.extend([mock_existing_seller, mock_existing_bidder1, mock_existing_bidder2, mock_existing_bidder3])
    mock_item = Item("testitem1", mock_existing_seller, None, 10, 10)
    backend.items.append(mock_item)
    bid1_transaction = Bid(mock_item,50,mock_existing_bidder1)
    bid2_transaction = Bid(mock_item,60,mock_existing_bidder2)
    bid3_transaction = Bid(mock_item,70,mock_existing_bidder3)
    transactions = [bid3_transaction, bid1_transaction, bid2_transaction, ]
    for transaction in transactions:
        try:
            transaction.process_transaction(backend)
        except:
            pass
    itemIndex = backend.items.index(mock_item)
    assert backend.items[itemIndex].top_bid == 70
    assert backend.items[itemIndex].top_bidder == mock_existing_bidder3

def test_bid_on_deleted_user_fails(backend):
    mock_existing_seller = SellStandard("testuser1", "password", 100)
    mock_existing_bidder = BuyStandard("testuser2", "password", 60)
    backend.users.append(mock_existing_seller)
    backend.users.append(mock_existing_bidder)
    mock_item = Item("testitem1", mock_existing_seller, None, 10, 10)
    backend.items.append(mock_item)
    delete_transaction = Delete(mock_existing_seller)
    delete_transaction.process_transaction(backend)
    bid_transaction = Bid(mock_item,50,mock_existing_bidder)
    with pytest.raises(Exception):
        bid_transaction.process_transaction(backend)
        
def test_bid_invalid_winning_bid_fails(backend):
    mock_existing_seller = SellStandard("testuser1", "password", 100)
    mock_existing_bidder = BuyStandard("testuser2", "password", 60)
    backend.users.extend([mock_existing_seller, mock_existing_bidder])
    mock_item = Item("testitem1", mock_existing_seller, None, 1, 30)
    backend.items.append(mock_item)
    bid_transaction = Bid(mock_item,70,mock_existing_bidder)
    with pytest.raises(Exception):  
        bid_transaction.process_transaction(backend)

def test_refund_succeeds(backend):
    mock_existing_seller = SellStandard("testuser1", "password", 100)
    mock_existing_buyer = BuyStandard("testuser2", "password", 60)
    backend.users.append(mock_existing_seller)
    backend.users.append(mock_existing_buyer)
    refund_transaction = Refund(mock_existing_seller,mock_existing_buyer,100)
    refund_transaction.process_transaction(backend)
    seller_index = backend.users.index(mock_existing_seller) 
    assert backend.users[seller_index].credit == 0
    buyer_index = backend.users.index(mock_existing_buyer)
    assert backend.users[buyer_index].credit == 160

def test_refund_from_deleted_seller_fails(backend):
    mock_seller = SellStandard("testuser1", "password", 0)
    mock_buyer = BuyStandard("testuser2", "password", 0)
    backend.users.extend([mock_seller, mock_buyer])
    delete_transaction = Delete(mock_seller)
    delete_transaction.process_transaction(backend)
    refund_transaction = Refund(mock_seller, mock_buyer, 0)
    with pytest.raises(Exception):
        refund_transaction.process_transaction(backend)

def test_refund_to_deleted_buyer_fails(backend):
    mock_seller = SellStandard("testuser1", "password", 0)
    mock_buyer = BuyStandard("testuser2", "password", 0)
    backend.users.extend([mock_seller, mock_buyer])
    delete_transaction = Delete(mock_buyer)
    delete_transaction.process_transaction(backend)
    refund_transaction = Refund(mock_seller, mock_buyer, 0)
    with pytest.raises(Exception):
        refund_transaction.process_transaction(backend)

def test_find_user_fails_if_user_does_not_exist(backend):
    mock_non_existing_user = FullStandard("testuser1", "password", 0)
    with pytest.raises(IndexError):
        backend.find_user(mock_non_existing_user)   

def test_find_user_succeeds_if_user_exists(backend):
    mock_existing_user = FullStandard("testuser1", "password", 0)
    backend.users.append(mock_existing_user)
    assert backend.find_user(mock_existing_user.username) == mock_existing_user

def test_find_item_fails_if_item_does_not_exist(backend):
    mock_seller = FullStandard("testseller1", "password", 0)
    mock_nonexisting_item = Item("testitem1", mock_seller, None, 1, 0)
    with pytest.raises(IndexError):
        backend.find_item(mock_nonexisting_item.item_name, mock_seller)
    
def test_find_item_succeeds_if_item_exists(backend):
    mock_seller = FullStandard("testseller1", "password", 0)
    mock_existing_item = Item("testitem1", mock_seller, None, 1, 0)
    backend.items.append(mock_existing_item)
    assert backend.find_item(mock_existing_item.item_name, mock_seller) == mock_existing_item

def test_set_available_users_succeeds(backend):
    with tempfile.NamedTemporaryFile(mode='w', delete=False) as temp:
        temp.write('TestAdmin001    AA 001000.00 password\n')
        temp.write('TestFull001     FS 001000.00 password\n')
        temp.write('END')
        temp.flush()
    
    backend.old_users_filepath = temp.name
    
    backend.set_available_users()
    
    assert len(backend.users) == 2
    assert backend.users[0].username == 'TestAdmin001'
    assert backend.users[0].privilege == 'AA'
    assert backend.users[0].credit == 1000.00
    assert backend.users[0].password == 'password'
    assert backend.users[1].username == 'TestFull001'
    assert backend.users[1].privilege == 'FS'
    assert backend.users[1].credit == 1000.00
    assert backend.users[1].password == 'password'

def test_set_available_items_succeeds(backend):
    mock_existing_user1 = Admin("TestAdmin001", "password", 1000.00)
    mock_existing_user2 = FullStandard("TestFull001", "password", 1000.00)
    mock_existing_user3 = BuyStandard("TestBuyer001", "password", 1000.00)
    mock_existing_user4 = SellStandard("TestSeller001", "password", 1000.00)
    
    backend.users.extend([mock_existing_user1, mock_existing_user2, mock_existing_user3, mock_existing_user4])
        
    with tempfile.NamedTemporaryFile(mode='w', delete=False) as temp2:
        temp2.write('TestItem001         TestSeller001   TestBuyer001   007 050.00\n')
        temp2.write('TestItem002         TestFull001     TestBuyer001   014 100.00\n')
        temp2.write('TestItem003         TestSeller001   TestFull001    021 150.00\n')
        temp2.write('END')
        temp2.flush()
        
    backend.old_items_filepath = temp2.name
    backend.set_available_items()
    
    assert len(backend.items) == 3
    assert backend.items[0].item_name == 'TestItem001'
    assert backend.items[0].seller == mock_existing_user4
    assert backend.items[0].top_bidder == mock_existing_user3
    assert backend.items[0].days_left == 7
    assert backend.items[0].top_bid == 50.00
