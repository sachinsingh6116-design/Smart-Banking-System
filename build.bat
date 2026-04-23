@echo off
REM Banking System Build Script for Windows
REM This script will help you build the Banking System

echo ===== BANKING SYSTEM BUILD SCRIPT =====
echo.

REM Check if g++ is available
where g++ >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    echo Found g++ compiler
    echo Compiling with g++...
    g++ -std=c++17 -o BankingSystem.exe main_gui.cpp BankAccount.cpp SavingsAccount.cpp CheckingAccount.cpp Transaction.cpp FileHandler.cpp -lstdc++fs -mwindows
    if %ERRORLEVEL% EQU 0 (
        echo.
        echo Build successful! Run the application with: BankingSystem.exe
    ) else (
        echo Build failed with g++
        exit /b 1
    )
    goto :end
)

REM Check if clang++ is available
where clang++ >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    echo Found clang++ compiler
    echo Compiling with clang++...
    clang++ -std=c++17 -o BankingSystem.exe main_gui.cpp BankAccount.cpp SavingsAccount.cpp CheckingAccount.cpp Transaction.cpp FileHandler.cpp -lstdc++fs -mwindows
    if %ERRORLEVEL% EQU 0 (
        echo.
        echo Build successful! Run the application with: BankingSystem.exe
    ) else (
        echo Build failed with clang++
        exit /b 1
    )
    goto :end
)

REM Check if Visual Studio cl.exe is available
where cl.exe >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    echo Found MSVC compiler
    echo Compiling with MSVC...
    cl /std:c++17 /W4 main.cpp BankAccount.cpp SavingsAccount.cpp CheckingAccount.cpp Transaction.cpp FileHandler.cpp /Fe:BankingSystem.exe
    if %ERRORLEVEL% EQU 0 (
        echo.
        echo Build successful! Run the application with: BankingSystem.exe
    ) else (
        echo Build failed with MSVC
        exit /b 1
    )
    goto :end
)

REM No compiler found
echo ERROR: No C++ compiler found on this system!
echo.
echo To build this project, you need to install one of the following:
echo.
echo Option 1: MinGW (Recommended for Windows)
echo   Download: https://www.mingw-w64.org/
echo   Add the bin directory to your PATH
echo.
echo Option 2: Visual Studio Community Edition
echo   Download: https://visualstudio.microsoft.com/vs/community/
echo   Install with C++ development tools
echo.
echo Option 3: LLVM/Clang
echo   Download: https://releases.llvm.org/download.html
echo   Add the bin directory to your PATH
echo.
echo After installation, run this script again.
exit /b 1

:end
echo.
pause
