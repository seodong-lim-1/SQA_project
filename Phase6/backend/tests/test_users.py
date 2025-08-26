import pytest
from ..src.Users.user import User
from ..src.Users.admin import Admin
from ..src.Users.fullstandard import FullStandard
from ..src.Users.buystandard import BuyStandard
from ..src.Users.sellstandard import SellStandard
from ..src.Users.accountmanager import AccountManager

# Test cases for valid username length
def test_user_succeeds():
    user = User("testuser", "US", "password", 100.0)
    assert user.username == "testuser"
    assert user.privilege == "US"
    assert user.password == "password"
    assert user.credit == 100.0

def test_admin_succeeds():
    admin = Admin("testuser", "password", 100.0)
    assert admin.username == "testuser"
    assert admin.privilege == "AA"
    assert admin.password == "password"
    assert admin.credit == 100.0

def test_fullstandard_succeeds():
    fs = FullStandard("testuser", "password", 100.0)
    assert fs.username == "testuser"
    assert fs.privilege == "FS"
    assert fs.password == "password"
    assert fs.credit == 100.0

def test_buystandard_succeeds():
    bs = BuyStandard("testuser", "password", 100.0)
    assert bs.username == "testuser"
    assert bs.privilege == "BS"
    assert bs.password == "password"
    assert bs.credit == 100.0

def test_sellstandard_succeeds():
    ss = SellStandard("testuser", "password", 100.0)
    assert ss.username == "testuser"
    assert ss.privilege == "SS"
    assert ss.password == "password"
    assert ss.credit == 100.0

def test_accountmanager_succeeds():
    am = AccountManager("testuser", "password", 100.0)
    assert am.username == "testuser"
    assert am.privilege == "AM"
    assert am.password == "password"
    assert am.credit == 100.0

# Test cases for invalid username length - too short
def test_user_invalid_username_too_short_fails():
    with pytest.raises(ValueError):
        User("", "US", "password", 100.0)

def test_admin_invalid_username_too_short_fails():
    with pytest.raises(ValueError):
        Admin("", "password", 100.0)

def test_fullstandard_invalid_username_too_short_fails():
    with pytest.raises(ValueError):
        FullStandard("", "password", 100.0)

def test_buystandard_invalid_username_too_short_fails():
    with pytest.raises(ValueError):
        BuyStandard("", "password", 100.0)

def test_sellstandard_invalid_username_too_short_fails():
    with pytest.raises(ValueError):
        SellStandard("", "password", 100.0)

def test_accountmanager_invalid_username_too_short_fails():
    with pytest.raises(ValueError):
        AccountManager("", "password", 100.0)

# Test cases for invalid username length - too long
long_username = "testusertestuser"

def test_user_invalid_username_too_long_fails():
    with pytest.raises(ValueError):
        User(long_username, "US", "password", 100.0)

def test_admin_invalid_username_too_long_fails():
    with pytest.raises(ValueError):
        Admin(long_username, "password", 100.0)

def test_fullstandard_invalid_username_too_long_fails():
    with pytest.raises(ValueError):
        FullStandard(long_username, "password", 100.0)

def test_buystandard_invalid_username_too_long_fails():
    with pytest.raises(ValueError):
        BuyStandard(long_username, "password", 100.0)

def test_sellstandard_invalid_username_too_long_fails():
    with pytest.raises(ValueError):
        SellStandard(long_username, "password", 100.0)

def test_accountmanager_invalid_username_too_long_fails():
    with pytest.raises(ValueError):
        AccountManager(long_username, "password", 100.0)

# Test cases for invalid password length - too short
def test_user_empty_password_fails():
    with pytest.raises(ValueError):
        User("testuser", "US", "", 100.0)

def test_admin_empty_password_fails():
    with pytest.raises(ValueError):
        Admin("testuser", "", 200.0)

def test_fullstandard_empty_password_fails():
    with pytest.raises(ValueError):
        FullStandard("testuser", "", 300.0)

def test_buystandard_empty_password_fails():
    with pytest.raises(ValueError):
        BuyStandard("testuser", "", 400.0)

def test_sellstandard_empty_password_fails():
    with pytest.raises(ValueError):
        SellStandard("testuser", "", 500.0)

def test_accountmanager_empty_password_fails():
    with pytest.raises(ValueError):
        AccountManager("testuser", "", 600.0)

# Test cases for invalid credit - too low
def test_user_invalid_credit_too_low_fails():
    with pytest.raises(ValueError):
        User("testuser", "US", "password", -1)

def test_admin_invalid_credit_too_low_fails():
    with pytest.raises(ValueError):
        Admin("testuser", "password", -1)

def test_fullstandard_invalid_credit_too_low_fails():
    with pytest.raises(ValueError):
        FullStandard("testuser", "password", -1)

def test_buystandard_invalid_credit_too_low_fails():
    with pytest.raises(ValueError):
        BuyStandard("testuser", "password", -1)

def test_sellstandard_invalid_credit_too_low_fails():
    with pytest.raises(ValueError):
        SellStandard("testuser", "password", -1)

def test_accountmanager_invalid_credit_too_low_fails():
    with pytest.raises(ValueError):
        AccountManager("testuser", "password", -1)

# Test cases for invalid credit - too high
def test_user_invalid_credit_too_high_fails():
    with pytest.raises(ValueError):
        User("testuser", "US", "password", 1000000)

def test_admin_invalid_credit_too_high_fails():
    with pytest.raises(ValueError):
        Admin("testuser", "password", 1000000)

def test_fullstandard_invalid_credit_too_high_fails():
    with pytest.raises(ValueError):
        FullStandard("testuser", "password", 1000000)

def test_buystandard_invalid_credit_too_high_fails():
    with pytest.raises(ValueError):
        BuyStandard("testuser", "password", 1000000)

def test_sellstandard_invalid_credit_too_high_fails():
    with pytest.raises(ValueError):
        SellStandard("testuser", "password", 1000000)

def test_accountmanager_invalid_credit_too_high_fails():
    with pytest.raises(ValueError):
        AccountManager("testuser", "password", 1000000)
