#include <iostream>
#include <vector>
#include <memory>
#include "BankAccount.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"
#include "FileHandler.h"
#include "utils.h"

using namespace std;

//  Helper function to find account
BankAccount* findAccount(vector<unique_ptr<BankAccount>>& accounts, string id) {
    for (auto& acc : accounts) {
        if (acc->getAccountNumber() == id) {
            return acc.get();
        }
    }
    return nullptr;
}

void displayMenu() {
    Utils::printSeparator();
    cout << "===== BANKING SYSTEM MENU =====\n";
    cout << "1. Create Account\n";
    cout << "2. Deposit\n";
    cout << "3. Withdraw\n";
    cout << "4. Transfer\n";
    cout << "5. View Account Info\n";
    cout << "6. Exit\n";
    cout << "===============================\n";
    cout << "Enter choice: ";
}

int main() {
    cout << "===== SMART BANKING SYSTEM =====\n";

    vector<unique_ptr<BankAccount>> accounts;

    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {

        // ✅ CREATE ACCOUNT
        case 1: {
            int type;
            string id, name;
            double balance;

            cout << "1. Basic\n2. Savings\n3. Checking\n";
            cout << "Enter type: ";
            cin >> type;

            cout << "Enter Account ID: ";
            cin >> id;

            cout << "Enter Name: ";
            cin >> name;

            cout << "Enter Initial Balance: ";
            cin >> balance;

            if (type == 1)
                accounts.push_back(make_unique<BankAccount>(id, name, balance));
            else if (type == 2)
                accounts.push_back(make_unique<SavingsAccount>(id, name, balance, 0.04));
            else
                accounts.push_back(make_unique<CheckingAccount>(id, name, balance, 1000));

            cout << "✅ Account Created Successfully!\n";
            break;
        }

        // ✅ DEPOSIT
        case 2: {
            string id;
            double amount;

            cout << "Enter Account ID: ";
            cin >> id;

            BankAccount* acc = findAccount(accounts, id);

            if (acc) {
                cout << "Enter amount: ";
                cin >> amount;
                acc->deposit(amount);
                cout << "✅ Deposit Successful\n";
            } else {
                cout << "❌ Account not found\n";
            }
            break;
        }

        // ✅ WITHDRAW
        case 3: {
            string id;
            double amount;

            cout << "Enter Account ID: ";
            cin >> id;

            BankAccount* acc = findAccount(accounts, id);

            if (acc) {
                cout << "Enter amount: ";
                cin >> amount;
                acc->withdraw(amount);
            } else {
                cout << "❌ Account not found\n";
            }
            break;
        }

        // ✅ TRANSFER
        case 4: {
            string fromId, toId;
            double amount;

            cout << "From Account ID: ";
            cin >> fromId;

            cout << "To Account ID: ";
            cin >> toId;

            cout << "Amount: ";
            cin >> amount;

            BankAccount* fromAcc = findAccount(accounts, fromId);
            BankAccount* toAcc = findAccount(accounts, toId);

            if (fromAcc && toAcc && fromAcc != toAcc) {
                fromAcc->transfer(*toAcc, amount);
                cout << "✅ Transfer Successful\n";
            } else {
                cout << "❌ Invalid accounts\n";
            }
            break;
        }

        // ✅ DISPLAY
        case 5: {
            string id;
            cout << "Enter Account ID: ";
            cin >> id;

            BankAccount* acc = findAccount(accounts, id);

            if (acc) {
                acc->displayAccountInfo();
            } else {
                cout << "❌ Account not found\n";
            }
            break;
        }

        // ✅ EXIT
        case 6:
            cout << "Thank you for using system!\n";
            return 0;

        default:
            cout << "Invalid choice\n";
        }
    }
}