#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>

// Utility functions for the banking system
namespace Utils {
    // Validate account number
    inline bool isValidAccountNumber(const std::string& accountNumber) {
        return accountNumber.length() >= 6 && accountNumber.length() <= 12;
    }

    // Validate deposit amount
    inline bool isValidAmount(double amount) {
        return amount > 0;
    }

    // Format currency
    inline std::string formatCurrency(double amount) {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << "$" << amount;
        return ss.str();
    }

    // Get current timestamp
    inline std::string getCurrentTimestamp() {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    // Print separator line
    inline void printSeparator() {
        std::cout << std::string(60, '-') << std::endl;
    }
}

#endif // UTILS_H
