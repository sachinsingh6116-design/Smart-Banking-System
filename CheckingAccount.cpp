#include "CheckingAccount.h"
#include "utils.h"
#include <iostream>

CheckingAccount::CheckingAccount(const std::string& accNum, const std::string& holder,
                                 double initialBalance, double overdraft)
    : BankAccount(accNum, holder, initialBalance), overdraftLimit(overdraft), 
      monthlyFee(10.0), checksIssued(0) {
    if (!transactionHistory.empty()) {
        transactionHistory.clear();
    }
    if (initialBalance > 0) {
        Transaction t("Initial Deposit (Checking)", initialBalance, balance);
        addTransaction(t);
    }
}

bool CheckingAccount::withdraw(double amount) {
    if (!Utils::isValidAmount(amount)) {
        std::cout << "Invalid withdrawal amount." << std::endl;
        return false;
    }
    double availableFunds = balance + overdraftLimit;
    if (amount > availableFunds) {
        std::cout << "Insufficient funds. Available: " << Utils::formatCurrency(availableFunds) << std::endl;
        return false;
    }
    balance -= amount;
    Transaction t("Withdrawal", amount, balance);
    addTransaction(t);
    std::cout << "Withdrew " << Utils::formatCurrency(amount) << ". New balance: "
              << Utils::formatCurrency(balance) << std::endl;
    
    if (balance < 0) {
        std::cout << "WARNING: Overdraft in use. Overdraft amount: " << Utils::formatCurrency(-balance) << std::endl;
    }
    return true;
}

void CheckingAccount::displayAccountInfo() const {
    Utils::printSeparator();
    std::cout << "Account Type: Checking Account" << std::endl;
    std::cout << "Account Number: " << accountNumber << std::endl;
    std::cout << "Account Holder: " << accountHolder << std::endl;
    std::cout << "Balance: " << Utils::formatCurrency(balance) << std::endl;
    std::cout << "Overdraft Limit: " << Utils::formatCurrency(overdraftLimit) << std::endl;
    std::cout << "Available Balance: " << Utils::formatCurrency(getAvailableBalance()) << std::endl;
    std::cout << "Checks Issued: " << checksIssued << std::endl;
    std::cout << "Monthly Fee: " << Utils::formatCurrency(monthlyFee) << std::endl;
    Utils::printSeparator();
}

double CheckingAccount::getAvailableBalance() const {
    return balance + overdraftLimit;
}

void CheckingAccount::issueCheck(double amount) {
    if (!withdraw(amount)) {
        return;
    }
    checksIssued++;
    std::cout << "Check #" << checksIssued << " issued for " << Utils::formatCurrency(amount) << std::endl;
}

void CheckingAccount::chargeMonthlyFee() {
    balance -= monthlyFee;
    Transaction t("Monthly Fee", monthlyFee, balance);
    addTransaction(t);
    std::cout << "Monthly fee of " << Utils::formatCurrency(monthlyFee) 
              << " charged. New balance: " << Utils::formatCurrency(balance) << std::endl;
}

void CheckingAccount::setMonthlyFee(double fee) {
    if (fee >= 0) {
        monthlyFee = fee;
        std::cout << "Monthly fee updated to " << Utils::formatCurrency(fee) << std::endl;
    } else {
        std::cout << "Invalid fee amount." << std::endl;
    }
}
