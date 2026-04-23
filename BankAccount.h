#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <vector>
#include "Transaction.h"

class BankAccount {
protected:
    std::string accountNumber;
    std::string accountHolder;
    double balance;
    std::vector<Transaction> transactionHistory;

public:
    // Constructor
    BankAccount(const std::string& accNum, const std::string& holder, double initialBalance = 0);

    // Virtual destructor
    virtual ~BankAccount() = default;

    // Getters
    std::string getAccountNumber() const;
    std::string getAccountHolder() const;
    double getBalance() const;

    // Virtual methods
    virtual void deposit(double amount);
    virtual bool withdraw(double amount);
    virtual void displayAccountInfo() const;

    // Transaction history
    void addTransaction(const Transaction& transaction);
    void displayTransactionHistory() const;
    std::vector<Transaction> getTransactionHistory() const;

    // Account management
    virtual bool transfer(BankAccount& recipient, double amount);
};

#endif // BANKACCOUNT_H
