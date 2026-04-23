#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include "BankAccount.h"

class FileHandler {
public:
    // File operations
    static bool saveAccountToFile(const BankAccount& account, const std::string& filename);
    static bool loadAccountFromFile(BankAccount& account, const std::string& filename);
    
    // Transaction log operations
    static bool saveTransactionLog(const BankAccount& account, const std::string& filename);
    static bool loadTransactionLog(BankAccount& account, const std::string& filename);
    
    // Utility methods
    static bool fileExists(const std::string& filename);
    static bool deleteFile(const std::string& filename);
};

#endif // FILEHANDLER_H
