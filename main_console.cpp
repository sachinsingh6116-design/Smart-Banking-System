#include <iostream>
#include <memory>
#include "BankAccount.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"
#include "FileHandler.h"
#include "utils.h"

using namespace std;

void displayMenu() {
    Utils::printSeparator();
    cout << "===== BANKING SYSTEM MENU =====" << endl;
    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "3. Transfer" << endl;
    cout << "4. View Account Info" << endl;
    cout << "5. View Transaction History" << endl;
    cout << "6. Apply Interest (Savings)" << endl;
    cout << "7. Issue Check (Checking)" << endl;
    cout << "8. Charge Monthly Fee (Checking)" << endl;
    cout << "9. Save Account to File" << endl;
    cout << "10. Exit" << endl;
    cout << "================================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    cout << "===== WELCOME TO BANKING SYSTEM =====" << endl << endl;

    // Create sample accounts
    cout << "Creating accounts..." << endl;
    BankAccount basicAccount("ACC001", "John Doe", 1000);
    SavingsAccount savingsAccount("SAV001", "Jane Smith", 5000, 0.04);
    CheckingAccount checkingAccount("CHK001", "Bob Johnson", 2000, 1000);

    cout << "Accounts created successfully!" << endl << endl;

    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1: { // Deposit
                cout << "\nSelect account: 1) Basic, 2) Savings, 3) Checking: ";
                int accChoice;
                cin >> accChoice;
                cout << "Enter amount to deposit: $";
                double amount;
                cin >> amount;

                if (accChoice == 1) {
                    basicAccount.deposit(amount);
                } else if (accChoice == 2) {
                    savingsAccount.deposit(amount);
                } else if (accChoice == 3) {
                    checkingAccount.deposit(amount);
                }
                break;
            }

            case 2: { // Withdraw
                cout << "\nSelect account: 1) Basic, 2) Savings, 3) Checking: ";
                int accChoice;
                cin >> accChoice;
                cout << "Enter amount to withdraw: $";
                double amount;
                cin >> amount;

                if (accChoice == 1) {
                    basicAccount.withdraw(amount);
                } else if (accChoice == 2) {
                    savingsAccount.withdraw(amount);
                } else if (accChoice == 3) {
                    checkingAccount.withdraw(amount);
                }
                break;
            }

            case 3: { // Transfer
                cout << "\nTransfer between accounts" << endl;
                cout << "From: 1) Basic, 2) Savings, 3) Checking: ";
                int fromChoice;
                cin >> fromChoice;
                cout << "To: 1) Basic, 2) Savings, 3) Checking: ";
                int toChoice;
                cin >> toChoice;
                cout << "Amount: $";
                double amount;
                cin >> amount;

                BankAccount* fromAcc = nullptr;
                BankAccount* toAcc = nullptr;

                if (fromChoice == 1) fromAcc = &basicAccount;
                else if (fromChoice == 2) fromAcc = &savingsAccount;
                else if (fromChoice == 3) fromAcc = &checkingAccount;

                if (toChoice == 1) toAcc = &basicAccount;
                else if (toChoice == 2) toAcc = &savingsAccount;
                else if (toChoice == 3) toAcc = &checkingAccount;

                if (fromAcc && toAcc && fromAcc != toAcc) {
                    fromAcc->transfer(*toAcc, amount);
                }
                break;
            }

            case 4: { // View Account Info
                cout << "\nSelect account: 1) Basic, 2) Savings, 3) Checking: ";
                int accChoice;
                cin >> accChoice;

                if (accChoice == 1) {
                    basicAccount.displayAccountInfo();
                } else if (accChoice == 2) {
                    savingsAccount.displayAccountInfo();
                } else if (accChoice == 3) {
                    checkingAccount.displayAccountInfo();
                }
                break;
            }

            case 5: { // View Transaction History
                cout << "\nSelect account: 1) Basic, 2) Savings, 3) Checking: ";
                int accChoice;
                cin >> accChoice;

                if (accChoice == 1) {
                    basicAccount.displayTransactionHistory();
                } else if (accChoice == 2) {
                    savingsAccount.displayTransactionHistory();
                } else if (accChoice == 3) {
                    checkingAccount.displayTransactionHistory();
                }
                break;
            }

            case 6: { // Apply Interest
                cout << "\nApplying interest to Savings Account..." << endl;
                savingsAccount.applyInterest();
                break;
            }

            case 7: { // Issue Check
                cout << "\nIssue check from Checking Account" << endl;
                cout << "Enter check amount: $";
                double amount;
                cin >> amount;
                checkingAccount.issueCheck(amount);
                break;
            }

            case 8: { // Charge Monthly Fee
                cout << "\nCharging monthly fee to Checking Account..." << endl;
                checkingAccount.chargeMonthlyFee();
                break;
            }

            case 9: { // Save to File
                cout << "\nSelect account to save: 1) Basic, 2) Savings, 3) Checking: ";
                int accChoice;
                cin >> accChoice;

                if (accChoice == 1) {
                    FileHandler::saveAccountToFile(basicAccount, "basic_account.txt");
                    FileHandler::saveTransactionLog(basicAccount, "basic_transactions.log");
                } else if (accChoice == 2) {
                    FileHandler::saveAccountToFile(savingsAccount, "savings_account.txt");
                    FileHandler::saveTransactionLog(savingsAccount, "savings_transactions.log");
                } else if (accChoice == 3) {
                    FileHandler::saveAccountToFile(checkingAccount, "checking_account.txt");
                    FileHandler::saveTransactionLog(checkingAccount, "checking_transactions.log");
                }
                break;
            }

            case 10: { // Exit
                cout << "\nThank you for using the Banking System. Goodbye!" << endl;
                running = false;
                break;
            }

            default:
                cout << "\nInvalid choice. Please try again." << endl;
        }
    }

    return 0;
}
