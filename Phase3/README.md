# CSCI3060U SQA Project

[Tests Spreadsheet](https://docs.google.com/spreadsheets/d/1ojG_lHD2hZNZkWCQqO6dmv66FIVD41fHsVvzNkjOIJg/edit?usp=sharing)

## Building, Compiling, & Usage

* Auction System is made for Unix systems, so it is recommended to use a Unix system. If you are using Windows, you can use [WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10).
* [Make sure your environment is setup for C++17](https://code.visualstudio.com/docs/languages/cpp)
  * Such as install g++, install make, etc
* Open terminal to the project directory.
* Type `make` in terminal to build.
* Type `./runtests.sh <tests run number:000-999>` in terminal to run system and all tests. If shell script is not executable, type `chmod +x runtests.sh` to give file execution privileges.
  * Example: `./runtests.sh 000`
* <details><summary>Or if want to manually run and test program...</summary>

   * Go to `bin/` directory via `cd bin/`.
   * Create these files: `Current_User_Accounts.txt`, `Available_Items.txt`, `Input_Stream.txt`.
   * Type `./auction-system` in terminal to run program.
      * Usage: `./auction-system <current_user_accounts_file> <available_items_file> <daily_transaction_file> < <input_stream_file>`
         * Example: `./auction-system Current_User_Accounts.txt Available_Items.txt Daily_Transaction.txt < Input_Stream.txt`
</details>

* And if needed, type `./cleantests.sh <tests run number:000-999 pr all>` in terminal to clean up all files created by tests. If shell script is not executable, type `chmod +x cleantests.sh` to give file execution privileges.
  * Example: `./cleantests.sh 000`

## Notable changes from Project.docx

1. `viewauctions` transaction that lists all items currently up for auctions
2. `viewusers` transaction that lists all available users; admin-only.
3. Password implementation system, with hashing.
4. Daily Transaction File regex changes such as:
   1. `XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC` into `XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC_PPPPPPPPPPPPPPPPPPPPPPPPP`
      1. `XX` is a two-digit transaction code: 01-create, 02-delete, 06-addcredit, 00-end of session
      2. `UUUUUUUUUUUUUUU` is the username
      3. `TT` is the user type (AA=admin, FS=full-standard, BS=buy-standard, SS=sell-standard)
      4. `CCCCCCCCC` is the available credit
      5. `PPPPPPPPPPPPPPPPPPPPPPPPP` is the hashed password; **added to include password implementation**
      6. `_` is a space
   2. `XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSS_DDD_PPPPPP` into `XX_IIIIIIIIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_DDD_BBBBBB`
      1. `XX` is a two-digit transaction code: 03-advertise.
      2. `IIIIIIIIIIIIIIIIIIIIIIIII` is the item name; **changed to max length 25 characters**
      3. `SSSSSSSSSSSSSSS` is the seller’s username; **changed to max length 15 characters**
      4. `DDD` is the number of days to auction
      5. `BBBBBB` is the minimum bid; **changed to better represent field**
      6. `_` is a space
   3. `XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUU_PPPPPP` into `XX_IIIIIIIIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUUU_DDD_BBBBBB`
      1. `XX` is a two-digit transaction code: 04-bid.
      2. `IIIIIIIIIIIIIIIIIIIIIIIII` is the item name; **changed to max length 25 characters**
      3. `SSSSSSSSSSSSSSS` is the seller’s username
      4. `UUUUUUUUUUUUUUU` is the buyer's username; **changed to max length 15 characters**
      5. `BBBBBB` is the new bid; **changed to better represent field**
      6. `_` is a space
5. User & Current User Accounts File regex changes such as:
   1. `UUUUUUUUUUUUUUU_TT_CCCCCCCCC` into `UUUUUUUUUUUUUUU_TT_CCCCCCCCC_PPPPPPPPPPPPPPPPPPPPPPPPP`
      1. `UUUUUUUUUUUUUUU` is the username
      2. `TT` is the user type (AA=admin, FS=full-standard, BS=buy-standard, SS=sell-standard)
      3. `CCCCCCCCC` is the available credit
      4. `PPPPPPPPPPPPPPPPPPPPPPPPP` is the hashed password; **added to include password implementation**
      5. `_` is a space
6. Item & Available Items regex changes such as:
   1. `IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUU_DDD_PPPPPP` into `IIIIIIIIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUUU_DDD_BBBBBB`
      1. `IIIIIIIIIIIIIIIIIIIIIIIII` is the item name; **changed to max length 25 characters**
      2. `SSSSSSSSSSSSSSS` is the seller’s username; **changed to max length 15 characters**
      3. `UUUUUUUUUUUUUUU` is the name of the user with the current winning bid; **changed to max length 15 characters**
      4. `DDD` is the number of days to auction
      5. `BBBBBB` is the minimum bid; **changed to better represent field**
      6. `_` is a space
