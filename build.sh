#!/bin/bash
# Banking System Build Script for Unix-like systems (Linux/Mac)

echo "===== BANKING SYSTEM BUILD SCRIPT ====="
echo

# Check for g++
if command -v g++ &> /dev/null; then
    echo "Found g++ compiler"
    echo "Compiling with g++..."
    g++ -std=c++17 -Wall -Wextra -o BankingSystem main.cpp BankAccount.cpp SavingsAccount.cpp CheckingAccount.cpp Transaction.cpp FileHandler.cpp -lstdc++fs
    if [ $? -eq 0 ]; then
        echo
        echo "Build successful!"
        echo "Run the application with: ./BankingSystem"
    else
        echo "Build failed with g++"
        exit 1
    fi
    exit 0
fi

# Check for clang++
if command -v clang++ &> /dev/null; then
    echo "Found clang++ compiler"
    echo "Compiling with clang++..."
    clang++ -std=c++17 -Wall -Wextra -o BankingSystem main.cpp BankAccount.cpp SavingsAccount.cpp CheckingAccount.cpp Transaction.cpp FileHandler.cpp -lstdc++fs
    if [ $? -eq 0 ]; then
        echo
        echo "Build successful!"
        echo "Run the application with: ./BankingSystem"
    else
        echo "Build failed with clang++"
        exit 1
    fi
    exit 0
fi

# Check if using CMake and make
if command -v cmake &> /dev/null && command -v make &> /dev/null; then
    echo "Found CMake and Make"
    echo "Building with CMake..."
    mkdir -p build
    cd build
    cmake ..
    make
    if [ $? -eq 0 ]; then
        echo
        echo "Build successful!"
        echo "Run the application with: ./BankingSystem"
    else
        echo "Build failed with CMake/Make"
        exit 1
    fi
    exit 0
fi

# No compiler found
echo "ERROR: No C++ compiler found on this system!"
echo
echo "To build this project, you need to install one of the following:"
echo
echo "For Ubuntu/Debian:"
echo "  sudo apt-get install build-essential"
echo
echo "For macOS:"
echo "  brew install gcc"
echo "  or use Xcode command line tools:"
echo "  xcode-select --install"
echo
echo "For Fedora/RHEL:"
echo "  sudo dnf install gcc-c++"
echo
echo "After installation, run this script again."
exit 1
