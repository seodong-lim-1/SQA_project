import pytest
from ..src.item import Item
from ..src.Users.sellstandard import SellStandard
from ..src.Users.buystandard import BuyStandard

def test_item_succeeds():
    seller = SellStandard("testuser1", "password", 100.0)
    top_bidder = BuyStandard("testuser2", "password", 200.0)
    item = Item("testitem1", seller, top_bidder, 10, 50.0)
    assert item.item_name == "testitem1"
    assert item.seller == seller
    assert item.top_bidder == top_bidder
    assert item.days_left == 10
    assert item.top_bid == 50.0

def test_item_invalid_item_name_too_short_fails():
    seller = SellStandard("testuser1", "password", 100.0)
    top_bidder = BuyStandard("testuser2", "password", 200.0)
    with pytest.raises(ValueError):
        Item("", seller, top_bidder, 10, 50.0)

def test_item_invalid_item_name_too_long_fails():
    seller = SellStandard("testuser1", "password", 100.0)
    top_bidder = BuyStandard("testuser2", "password", 200.0)
    long_item_name = "testitemtestitemtestitemtestitem"
    with pytest.raises(ValueError):
        Item(long_item_name, seller, top_bidder, 10, 50.0)

def test_item_invalid_top_bid_too_low_fails():
    seller = SellStandard("testuser1", "password", 100.0)
    top_bidder = BuyStandard("testuser2", "password", 200.0)
    with pytest.raises(ValueError):
        Item("testitem1", seller, top_bidder, 10, -1)

def test_item_invalid_top_bid_too_high_fails():
    seller = SellStandard("testuser1", "password", 100.0)
    top_bidder = BuyStandard("testuser2", "password", 200.0)
    with pytest.raises(ValueError):
        Item("testitem1", seller, top_bidder, 10, 1000.0)

def test_item_invalid_days_left_too_low_fails():
    seller = SellStandard("testuser1", "password", 100.0)
    top_bidder = BuyStandard("testuser2", "password", 200.0)
    with pytest.raises(ValueError):
        Item("testitem1", seller, top_bidder, 0, 50.0)

def test_item_invalid_days_left_too_high_fails():
    seller = SellStandard("testuser1", "password", 100.0)
    top_bidder = BuyStandard("testuser2", "password", 200.0)
    with pytest.raises(ValueError):
        Item("testitem1", seller, top_bidder, 101, 50.0)

def test_item_invalid_seller_fails():
    seller = "invalid_seller"
    top_bidder = BuyStandard("testuser2", "password", 200.0)
    with pytest.raises(ValueError):
        Item("testitem1", seller, top_bidder, 10, 50.0)

def test_item_invalid_top_bidder_fails():
    seller = SellStandard("testuser1", "password", 100.0)
    top_bidder = "invalid_top_bidder"
    with pytest.raises(ValueError):
        Item("testitem1", seller, top_bidder, 10, 50.0)
