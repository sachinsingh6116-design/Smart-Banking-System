#include "SavingsAccount.h"
#include "utils.h"
#include <iostream>

const double SavingsAccount::MIN_BALANCE = 100.0;

SavingsAccount::SavingsAccount(const std::string& accNum, const std::string& holder,
                               double initialBalance, double rate)
    : BankAccount(accNum, holder, initialBalance), interestRate(rate) {
    // Replace the initial deposit description
    if (!transactionHistory.empty()) {
        transactionHistory.clear();
    }
    if (initialBalance > 0) {
        Transaction t("Initial Deposit (Savings)", initialBalance, balance);
        addTransaction(t);
    }
}

bool SavingsAccount::withdraw(double amount) {
    if (!Utils::isValidAmount(amount)) {
        std::cout << "Invalid withdrawal amount." << std::endl;
        return false;
    }
    if (amount > balance) {
        std::cout << "Insufficient funds." << std::endl;
        return false;
    }
    if ((balance - amount) < MIN_BALANCE) {
        std::cout << "Withdrawal failed! Minimum balance required: " << Utils::formatCurrency(MIN_BALANCE) << std::endl;
        std::cout << "Current balance would be: " << Utils::formatCurrency(balance - amount) << std::endl;
        return false;
    }
    balance -= amount;
    Transaction t("Withdrawal", amount, balance);
    addTransaction(t);
    std::cout << "Withdrew " << Utils::formatCurrency(amount) << ". New balance: "
              << Utils::formatCurrency(balance) << std::endl;
    return true;
}

void SavingsAccount::displayAccountInfo() const {
    Utils::printSeparator();
    std::cout << "Account Type: Savings Account" << std::endl;
    std::cout << "Account Number: " << accountNumber << std::endl;
    std::cout << "Account Holder: " << accountHolder << std::endl;
    std::cout << "Balance: " << Utils::formatCurrency(balance) << std::endl;
    std::cout << "Interest Rate: " << (interestRate * 100) << "%" << std::endl;
    std::cout << "Minimum Balance Required: " << Utils::formatCurrency(MIN_BALANCE) << std::endl;
    Utils::printSeparator();
}

void SavingsAccount::applyInterest() {
    double interest = balance * interestRate;
    balance += interest;
    Transaction t("Interest Credit", interest, balance);
    addTransaction(t);
    std::cout << "Interest of " << Utils::formatCurrency(interest) << " applied. "
              << "New balance: " << Utils::formatCurrency(balance) << std::endl;
}

double SavingsAccount::getInterestRate() const {
    return interestRate;
}

void SavingsAccount::setInterestRate(double rate) {
    if (rate >= 0 && rate <= 1.0) {
        interestRate = rate;
        std::cout << "Interest rate updated to " << (rate * 100) << "%" << std::endl;
    } else {
        std::cout << "Invalid interest rate. Must be between 0 and 1.0" << std::endl;
    }
}
