# Phase 5

## How to run or test the code

1. `cd` into `Phase5`
2. `python -m backend.src.main backend/database/Current_User_Accounts.txt backend/database/Available_Items.txt`
3. `python -m pytest backend/tests/test_backend.py`

## Changes

1. Added new user type called Account Manager (AM), who cannot Bid or Advertise, but can do any other Admin transaction. But also can't create or delete any Admins.
2. Only processes highest bid for each item
3. If the winning bidder doesnt have enough funds, the auction is cancelled and the item is removed from system
4. If bidder doesnt have enough funds, bid is cancelled.
