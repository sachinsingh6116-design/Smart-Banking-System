cmake_minimum_required(VERSION 3.10)
project(BankingSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    main.cpp
    BankAccount.cpp
    SavingsAccount.cpp
    CheckingAccount.cpp
    Transaction.cpp
    FileHandler.cpp
)

# Create executable
add_executable(BankingSystem ${SOURCES})

# Set output directory
set_target_properties(BankingSystem PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Link filesystem library for older compilers
target_link_libraries(BankingSystem PRIVATE stdc++fs)
