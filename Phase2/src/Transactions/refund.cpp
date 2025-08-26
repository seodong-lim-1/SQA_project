#include "../include/Transactions/refund.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Refund::processTransaction() {
    // TODO issue a credit to a buyer’s account from a seller’s account (privileged transaction)
    // TODO should ask for the buyer’s username, the seller’s username and the amount of credit to transfer.
    // TODO should transfer the specified amount of credit from the seller’s credit balance to the buyer’s credit balance.
    // TODO should save this information for the daily transaction file
    // TODO Buyer and seller both must be current users
     private:
        string buyerUsername;
        string sellerUsername;
        double transferAmount;
        unordered_map<string, double> userCreditBalance; // user credit balance
        
    public:
        refund() {
            // Initialize user credit balances
            userCreditBalance["buyer123"] = 1000.0;
            userCreditBalance["seller456"] = 2000.0;
        }
        
        void askUserInput() {
            // Ask for user input
            cout << "Enter buyer's username: ";
            cin >> buyerUsername;
            cout << "Enter seller's username: ";
            cin >> sellerUsername;
            cout << "Enter transfer amount: ";
            cin >> transferAmount;
        }
        
        bool validateUsers() {
            // Check if the buyer and seller are current users
            if (userCreditBalance.find(buyerUsername) == userCreditBalance.end() ||
                userCreditBalance.find(sellerUsername) == userCreditBalance.end()) {
                return false;
            }
            
            return true;
        }
        
        void performTransaction() {
            if (!validateUsers()) {
                cout << "Error: Buyer or seller is not a current user." << endl;
                return;
            }
            
            double buyerBalance = userCreditBalance[buyerUsername];
            double sellerBalance = userCreditBalance[sellerUsername];
            
            if (sellerBalance < transferAmount) {
                cout << "Error: Seller does not have enough credit to transfer." << endl;
                return;
            }
            
            // Transfer credit from seller to buyer
            sellerBalance -= transferAmount;
            buyerBalance += transferAmount;
            
            // Update user credit balances
            userCreditBalance[sellerUsername] = sellerBalance;
            userCreditBalance[buyerUsername] = buyerBalance;
            
            // Save transaction information to daily transaction file
            ofstream transactionFile("daily_transaction_file.txt", ios_base::app);
            transactionFile << buyerUsername << " bought " << transferAmount << " credit from " << sellerUsername << endl;
            transactionFile.close();
            
            cout << "Successfully transferred " << transferAmount << " credit from " << sellerUsername << " to " << buyerUsername << "." << endl;
        }
};
