#include "Transaction.h"
#include "utils.h"
#include <iostream>
#include <sstream>

Transaction::Transaction(const std::string& type, double amt, double balance)
    : transactionType(type), amount(amt), balanceAfter(balance) {
    timestamp = Utils::getCurrentTimestamp();
}

std::string Transaction::getType() const {
    return transactionType;
}

double Transaction::getAmount() const {
    return amount;
}

std::string Transaction::getTimestamp() const {
    return timestamp;
}

double Transaction::getBalanceAfter() const {
    return balanceAfter;
}

void Transaction::display() const {
    std::cout << "Type: " << transactionType << " | Amount: " << Utils::formatCurrency(amount)
              << " | Time: " << timestamp << " | Balance: " << Utils::formatCurrency(balanceAfter)
              << std::endl;
}

std::string Transaction::toString() const {
    return transactionType + "|" + std::to_string(amount) + "|" + timestamp + "|" + std::to_string(balanceAfter);
}

Transaction Transaction::fromString(const std::string& str) {
    std::stringstream ss(str);
    std::string type, amtStr, time, balStr;
    
    std::getline(ss, type, '|');
    std::getline(ss, amtStr, '|');
    std::getline(ss, time, '|');
    std::getline(ss, balStr, '|');
    
    double amount = std::stod(amtStr);
    double balance = std::stod(balStr);
    
    Transaction t(type, amount, balance);
    t.timestamp = time;
    return t;
}
