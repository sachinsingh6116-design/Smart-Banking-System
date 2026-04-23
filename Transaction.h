#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>
#include <ctime>

class Transaction {
private:
    std::string transactionType;  // "Deposit", "Withdrawal", "Transfer"
    double amount;
    std::string timestamp;
    double balanceAfter;

public:
    // Constructor
    Transaction(const std::string& type, double amt, double balance);

    // Getters
    std::string getType() const;
    double getAmount() const;
    std::string getTimestamp() const;
    double getBalanceAfter() const;

    // Display transaction
    void display() const;

    // Convert to string for file storage
    std::string toString() const;

    // Create from string
    static Transaction fromString(const std::string& str);
};

#endif // TRANSACTION_H
