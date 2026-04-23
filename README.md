# Banking System - C++ Project

A comprehensive C++ banking system with support for multiple account types, transactions, and file persistence.

## Project Structure

```
BankingSystem/
├── main.cpp              # Main application entry point
├── BankAccount.h/cpp     # Base account class
├── SavingsAccount.h/cpp  # Savings account with interest rates
├── CheckingAccount.h/cpp # Checking account with overdraft capability
├── Transaction.h/cpp     # Transaction history tracking
├── FileHandler.h/cpp     # File I/O operations
├── utils.h               # Utility functions
├── CMakeLists.txt        # CMake build configuration
├── Makefile             # Make build configuration
└── README.md            # This file
```

## Features

### Account Types
1. **Basic Bank Account**: Standard savings/checking with deposit/withdraw
2. **Savings Account**: Higher interest rates, minimum balance requirement
3. **Checking Account**: Overdraft capability, check issuance, monthly fees

### Core Features
- Deposit and withdrawal operations
- Fund transfers between accounts
- Transaction history tracking with timestamps
- Interest calculation for savings accounts
- Overdraft protection for checking accounts
- File persistence (save/load account data and transaction logs)
- Comprehensive transaction logging

## Building the Project

### Prerequisites: Install a C++ Compiler

**Windows:**
- MinGW-w64: https://www.mingw-w64.org/
- Or Visual Studio Community: https://visualstudio.microsoft.com/vs/community/
- Or LLVM/Clang: https://releases.llvm.org/download.html

**Linux (Ubuntu/Debian):**
```bash
sudo apt-get install build-essential
```

**Linux (Fedora/RHEL):**
```bash
sudo dnf install gcc-c++
```

**macOS:**
```bash
brew install gcc
# or use Xcode
xcode-select --install
```

### Option 1: Using the Build Script (Recommended)

**Windows:**
```bash
build.bat
```

**Linux/Mac:**
```bash
chmod +x build.sh
./build.sh
```

### Option 2: Using CMake
```bash
cd BankingSystem
mkdir build
cd build
cmake ..
cmake --build .
```

### Option 3: Using Make
```bash
cd BankingSystem
make
```

### Option 4: Manual Compilation (g++)
```bash
cd BankingSystem
g++ -std=c++17 -o BankingSystem main.cpp BankAccount.cpp SavingsAccount.cpp CheckingAccount.cpp Transaction.cpp FileHandler.cpp -lstdc++fs
```

### Option 5: Manual Compilation (MSVC on Windows)
```bash
cd BankingSystem
cl /std:c++17 main.cpp BankAccount.cpp SavingsAccount.cpp CheckingAccount.cpp Transaction.cpp FileHandler.cpp /Fe:BankingSystem.exe
```

### Option 6: Manual Compilation (Clang)
```bash
cd BankingSystem
clang++ -std=c++17 -o BankingSystem main.cpp BankAccount.cpp SavingsAccount.cpp CheckingAccount.cpp Transaction.cpp FileHandler.cpp -lstdc++fs
```

## Running the Application

After building with any method above:

**Windows:**
```bash
BankingSystem.exe
```

**Linux/Mac:**
```bash
./BankingSystem
```

Or using Make:
```bash
make run
```

## Usage Guide

The application provides an interactive menu system:

1. **Deposit**: Add funds to an account
2. **Withdraw**: Remove funds from an account
3. **Transfer**: Move funds between accounts
4. **View Account Info**: See account details and balance
5. **View Transaction History**: Review all account transactions
6. **Apply Interest**: Calculate and apply interest (Savings only)
7. **Issue Check**: Write a check (Checking only)
8. **Charge Monthly Fee**: Apply monthly fee (Checking only)
9. **Save Account**: Export account data and transaction log to files
10. **Exit**: Close the application

## Account Details

### Basic Account
- Minimum balance: $0
- Features: Deposit, Withdraw, Transfer

### Savings Account
- Minimum balance: $100
- Interest rate: 4% (default, configurable)
- Features: Deposit, Withdraw (with minimum balance check), Transfer, Interest

### Checking Account
- Overdraft limit: $500 (configurable)
- Monthly fee: $10 (configurable)
- Features: Deposit, Withdraw, Transfer, Check issuance, Monthly fees

## Example Session

```
1. Create accounts
2. Deposit $1000 to Savings Account
3. Apply 4% interest → Balance becomes $1040
4. Transfer $500 to Checking Account
5. Issue a check for $300 from Checking Account
6. View transaction history
7. Save account data to file
8. Exit
```

## Technical Details

### Requirements
- C++17 or later
- CMake 3.10+ (for CMake build)
- Make (for Makefile build)
- GCC/Clang/MSVC compiler with C++17 support

### Key Classes
- **BankAccount**: Base class with core banking operations
- **SavingsAccount**: Extends BankAccount with interest functionality
- **CheckingAccount**: Extends BankAccount with overdraft and check features
- **Transaction**: Records and stores transaction details
- **FileHandler**: Manages file I/O for persistence

### Supported Operations
- Deposit/Withdraw with validation
- Fund transfers with automatic logging
- Interest calculation and application
- Check issuance with automatic withdrawal
- File saving and loading of account data
- Transaction history export

## File Output

When saving accounts, the following files are created:
- `*_account.txt`: Account information (number, holder, balance)
- `*_transactions.log`: Transaction history in CSV format

## Error Handling

The system includes validation for:
- Invalid amounts (negative or zero)
- Insufficient funds
- Overdraft limits
- Minimum balance requirements
- File I/O operations

## Future Enhancements

Possible additions:
- Database integration (SQLite, PostgreSQL)
- Multi-user authentication system
- Credit card accounts
- Loan management
- Investment accounts
- Mobile app integration
- Web dashboard

## License

This project is provided as-is for educational purposes.

## Author

Banking System Tutorial - C++ OOP Implementation

---

For questions or issues, please refer to the source code documentation.
