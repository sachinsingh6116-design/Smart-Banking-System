#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "BankAccount.h"

class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;
    double monthlyFee;
    int checksIssued;

public:
    // Constructor
    CheckingAccount(const std::string& accNum, const std::string& holder,
                    double initialBalance = 0, double overdraft = 500.0);

    // Override methods
    bool withdraw(double amount) override;
    void displayAccountInfo() const override;

    // Checking-specific methods
    double getAvailableBalance() const;
    void issueCheck(double amount);
    void chargeMonthlyFee();
    void setMonthlyFee(double fee);
};

#endif // CHECKINGACCOUNT_H
