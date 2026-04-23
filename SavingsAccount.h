#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "BankAccount.h"

class SavingsAccount : public BankAccount {
private:
    double interestRate;
    static const double MIN_BALANCE;

public:
    // Constructor
    SavingsAccount(const std::string& accNum, const std::string& holder, 
                   double initialBalance = 0, double rate = 0.03);

    // Override methods
    bool withdraw(double amount) override;
    void displayAccountInfo() const override;

    // Savings-specific methods
    void applyInterest();
    double getInterestRate() const;
    void setInterestRate(double rate);
};

#endif // SAVINGSACCOUNT_H
