#include "BankAccount.h"
#include "utils.h"
#include <iostream>

BankAccount::BankAccount(const std::string& accNum, const std::string& holder, double initialBalance)
    : accountNumber(accNum), accountHolder(holder), balance(initialBalance) {
    if (initialBalance > 0) {
        Transaction t("Initial Deposit", initialBalance, balance);
        addTransaction(t);
    }
}

std::string BankAccount::getAccountNumber() const {
    return accountNumber;
}

std::string BankAccount::getAccountHolder() const {
    return accountHolder;
}

double BankAccount::getBalance() const {
    return balance;
}

void BankAccount::deposit(double amount) {
    if (!Utils::isValidAmount(amount)) {
        std::cout << "Invalid deposit amount. Amount must be positive." << std::endl;
        return;
    }
    balance += amount;
    Transaction t("Deposit", amount, balance);
    addTransaction(t);
    std::cout << "Deposited " << Utils::formatCurrency(amount) << ". New balance: "
              << Utils::formatCurrency(balance) << std::endl;
}

bool BankAccount::withdraw(double amount) {
    if (!Utils::isValidAmount(amount)) {
        std::cout << "Invalid withdrawal amount. Amount must be positive." << std::endl;
        return false;
    }
    if (amount > balance) {
        std::cout << "Insufficient funds. Current balance: " << Utils::formatCurrency(balance) << std::endl;
        return false;
    }
    balance -= amount;
    Transaction t("Withdrawal", amount, balance);
    addTransaction(t);
    std::cout << "Withdrew " << Utils::formatCurrency(amount) << ". New balance: "
              << Utils::formatCurrency(balance) << std::endl;
    return true;
}

void BankAccount::displayAccountInfo() const {
    Utils::printSeparator();
    std::cout << "Account Type: Basic Bank Account" << std::endl;
    std::cout << "Account Number: " << accountNumber << std::endl;
    std::cout << "Account Holder: " << accountHolder << std::endl;
    std::cout << "Balance: " << Utils::formatCurrency(balance) << std::endl;
    Utils::printSeparator();
}

void BankAccount::addTransaction(const Transaction& transaction) {
    transactionHistory.push_back(transaction);
}

void BankAccount::displayTransactionHistory() const {
    if (transactionHistory.empty()) {
        std::cout << "No transactions found." << std::endl;
        return;
    }
    Utils::printSeparator();
    std::cout << "Transaction History for " << accountNumber << std::endl;
    Utils::printSeparator();
    for (const auto& transaction : transactionHistory) {
        transaction.display();
    }
    Utils::printSeparator();
}

std::vector<Transaction> BankAccount::getTransactionHistory() const {
    return transactionHistory;
}

bool BankAccount::transfer(BankAccount& recipient, double amount) {
    if (!Utils::isValidAmount(amount)) {
        std::cout << "Invalid transfer amount." << std::endl;
        return false;
    }
    if (amount > balance) {
        std::cout << "Insufficient funds for transfer." << std::endl;
        return false;
    }
    this->withdraw(amount);
    recipient.deposit(amount);
    
    Transaction senderTransaction("Transfer Out", amount, balance);
    addTransaction(senderTransaction);
    
    return true;
}
