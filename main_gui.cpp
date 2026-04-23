#include <windows.h>
#include <sstream>
#include <functional>
#include <string>
#include <iostream>
#include "BankAccount.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"
#include "FileHandler.h"

using namespace std;

// Accounts
static BankAccount basicAccount("ACC001", "Sachin Singh", 500000);
static SavingsAccount savingsAccount("SAV001", "Aayush Kumar", 50000, 0.04);
static CheckingAccount checkingAccount("CHK001", "Narayan Patidar", 20000, 10000);

// UI Handles
HWND hLog, hAccountCombo, hAmountEdit, hBalanceEdit;

HFONT hFont;
HBRUSH hBrush;

string logData;

// Capture output
string capture(function<void()> fn) {
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    fn();
    cout.rdbuf(old);
    return buffer.str();
}

// Logging
void log(string text) {
    logData += text + "\r\n";
    SetWindowTextA(hLog, logData.c_str());
    SendMessage(hLog, EM_SETSEL, -1, -1);
    SendMessage(hLog, EM_SCROLLCARET, 0, 0);
}

// Get account
BankAccount* getAcc(int i) {
    if(i==0) return &basicAccount;
    if(i==1) return &savingsAccount;
    return &checkingAccount;
}

// Init combo
void initCombo(HWND c) {
    SendMessageA(c, CB_ADDSTRING,0,(LPARAM)"Basic - Sachin Singh");
    SendMessageA(c, CB_ADDSTRING,0,(LPARAM)"Savings - Aayush Kumar");
    SendMessageA(c, CB_ADDSTRING,0,(LPARAM)"Checking - Narayan Patidar");
    SendMessageA(c, CB_SETCURSEL,0,0);
}

// 🔥 FIX: update balance UI
void updateBalanceUI(BankAccount* acc) {
    if (!acc) return;

    char buffer[100];
    sprintf(buffer, "%.2f", acc->getBalance());

    SetWindowTextA(hBalanceEdit, buffer);
}

// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {

    switch(msg) {

    case WM_CREATE: {

        hFont = CreateFontA(20,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,0,0,0,0,"Segoe UI");
        hBrush = CreateSolidBrush(RGB(240,245,250));

        CreateWindowA("STATIC","SMART BANKING SYSTEM",
            WS_VISIBLE|WS_CHILD,
            300,10,300,30,hwnd,NULL,NULL,NULL);

        // Account
        CreateWindowA("STATIC","Select Account:",
            WS_VISIBLE|WS_CHILD,30,60,150,20,hwnd,NULL,NULL,NULL);

        hAccountCombo = CreateWindowA("COMBOBOX","",
            WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST,
            180,60,250,200,hwnd,(HMENU)1002,NULL,NULL);

        initCombo(hAccountCombo);

        // Amount
        CreateWindowA("STATIC","Amount:",
            WS_VISIBLE|WS_CHILD,30,100,150,20,hwnd,NULL,NULL,NULL);

        hAmountEdit = CreateWindowA("EDIT","",
            WS_VISIBLE|WS_CHILD|WS_BORDER,
            180,100,250,30,hwnd,(HMENU)1003,NULL,NULL);

        // Balance
        CreateWindowA("STATIC","Balance:",
            WS_VISIBLE|WS_CHILD,30,140,150,20,hwnd,NULL,NULL,NULL);

        hBalanceEdit = CreateWindowA("EDIT","",
            WS_VISIBLE|WS_CHILD|WS_BORDER|ES_READONLY,
            180,140,250,30,hwnd,(HMENU)1006,NULL,NULL);

        // Buttons
        int x = 480, y = 60;

        CreateWindowA("BUTTON","Deposit",WS_VISIBLE|WS_CHILD,x,y,160,40,hwnd,(HMENU)1,NULL,NULL);
        CreateWindowA("BUTTON","Withdraw",WS_VISIBLE|WS_CHILD,x,y+50,160,40,hwnd,(HMENU)2,NULL,NULL);
        CreateWindowA("BUTTON","Transfer",WS_VISIBLE|WS_CHILD,x,y+100,160,40,hwnd,(HMENU)3,NULL,NULL);
        CreateWindowA("BUTTON","View Info",WS_VISIBLE|WS_CHILD,x,y+150,160,40,hwnd,(HMENU)4,NULL,NULL);
        CreateWindowA("BUTTON","History",WS_VISIBLE|WS_CHILD,x,y+200,160,40,hwnd,(HMENU)5,NULL,NULL);
        CreateWindowA("BUTTON","Apply Interest",WS_VISIBLE|WS_CHILD,x,y+250,160,40,hwnd,(HMENU)6,NULL,NULL);
        CreateWindowA("BUTTON","Issue Check",WS_VISIBLE|WS_CHILD,x,y+300,160,40,hwnd,(HMENU)7,NULL,NULL);
        CreateWindowA("BUTTON","Charge Fee",WS_VISIBLE|WS_CHILD,x,y+350,160,40,hwnd,(HMENU)8,NULL,NULL);
        CreateWindowA("BUTTON","Save",WS_VISIBLE|WS_CHILD,x,y+400,160,40,hwnd,(HMENU)9,NULL,NULL);
        CreateWindowA("BUTTON","Exit",WS_VISIBLE|WS_CHILD,x,y+450,160,40,hwnd,(HMENU)10,NULL,NULL);

        // Log
        hLog = CreateWindowA("EDIT","",
            WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE|ES_READONLY|WS_VSCROLL,
            30,200,400,350,hwnd,NULL,NULL,NULL);

        SendMessage(hLog, WM_SETFONT,(WPARAM)hFont,TRUE);

        // Initial balance
        updateBalanceUI(&basicAccount);

        log("GUI Ready");

    } return 0;

    case WM_COMMAND: {

        // 🔥 FIX: update when account changes
        if (HIWORD(wp) == CBN_SELCHANGE && LOWORD(wp) == 1002) {
            int idx = SendMessage(hAccountCombo, CB_GETCURSEL,0,0);
            BankAccount* acc = getAcc(idx);
            updateBalanceUI(acc);
            return 0;
        }

        int id = LOWORD(wp);
        int idx = SendMessage(hAccountCombo, CB_GETCURSEL,0,0);
        BankAccount* acc = getAcc(idx);

        char buf[50];
        GetWindowTextA(hAmountEdit,buf,50);

        double amt = 0;
        if(strlen(buf) > 0) amt = atof(buf);

        switch(id) {

        case 1:
            log(capture([&](){ acc->deposit(amt); }));
            updateBalanceUI(acc);
            break;

        case 2:
            log(capture([&](){ acc->withdraw(amt); }));
            updateBalanceUI(acc);
            break;

        case 3:
            log(capture([&](){ acc->transfer(*acc,amt); }));
            updateBalanceUI(acc);
            break;

        case 4:
            log(capture([&](){ acc->displayAccountInfo(); }));
            break;

        case 5:
            log(capture([&](){ acc->displayTransactionHistory(); }));
            break;

        case 6:
            if(auto s=dynamic_cast<SavingsAccount*>(acc)) {
                log(capture([&](){ s->applyInterest(); }));
                updateBalanceUI(acc);
            }
            break;

        case 7:
            if(auto c=dynamic_cast<CheckingAccount*>(acc)) {
                log(capture([&](){ c->issueCheck(amt); }));
                updateBalanceUI(acc);
            }
            break;

        case 8:
            if(auto c=dynamic_cast<CheckingAccount*>(acc)) {
                log(capture([&](){ c->chargeMonthlyFee(); }));
                updateBalanceUI(acc);
            }
            break;

        case 9:
            FileHandler::saveAccountToFile(*acc,"account.txt");
            log("Saved to file");
            break;

        case 10:
            PostQuitMessage(0);
            break;
        }

    } return 0;

    case WM_CTLCOLORSTATIC:
    case WM_CTLCOLOREDIT:
        SetBkColor((HDC)wp, RGB(240,245,250));
        return (INT_PTR)hBrush;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd,msg,wp,lp);
}

// Main
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int nShow) {

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "BankGUI";

    RegisterClass(&wc);

    HWND hwnd = CreateWindow("BankGUI","Smart Banking System",
        WS_OVERLAPPEDWINDOW,
        100,100,1000,650,
        NULL,NULL,hInst,NULL);

    ShowWindow(hwnd,nShow);

    MSG msg;
    while(GetMessage(&msg,NULL,0,0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}