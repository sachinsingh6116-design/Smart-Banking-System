#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

bool FileHandler::saveAccountToFile(const BankAccount& account, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return false;
    }

    outFile << account.getAccountNumber() << std::endl;
    outFile << account.getAccountHolder() << std::endl;
    outFile << account.getBalance() << std::endl;

    outFile.close();
    std::cout << "Account data saved to " << filename << std::endl;
    return true;
}

bool FileHandler::loadAccountFromFile(BankAccount& account, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for reading." << std::endl;
        return false;
    }

    std::string accountNumber, accountHolder;
    double balance;

    std::getline(inFile, accountNumber);
    std::getline(inFile, accountHolder);
    inFile >> balance;

    inFile.close();
    std::cout << "Account data loaded from " << filename << std::endl;
    return true;
}

bool FileHandler::saveTransactionLog(const BankAccount& account, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return false;
    }

    auto history = account.getTransactionHistory();
    for (const auto& transaction : history) {
        outFile << transaction.toString() << std::endl;
    }

    outFile.close();
    std::cout << "Transaction log saved to " << filename << std::endl;
    return true;
}

bool FileHandler::loadTransactionLog(BankAccount& account, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for reading." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            Transaction t = Transaction::fromString(line);
            account.addTransaction(t);
        }
    }

    inFile.close();
    std::cout << "Transaction log loaded from " << filename << std::endl;
    return true;
}

bool FileHandler::fileExists(const std::string& filename) {
    return fs::exists(filename);
}

bool FileHandler::deleteFile(const std::string& filename) {
    if (fs::exists(filename)) {
        fs::remove(filename);
        std::cout << "File " << filename << " deleted." << std::endl;
        return true;
    }
    std::cerr << "File " << filename << " does not exist." << std::endl;
    return false;
}
