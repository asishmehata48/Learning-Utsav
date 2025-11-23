#ifndef BANKINGSYSTEM_H
#define BANKINGSYSTEM_H

#include "Account.h"
#include <unordered_map>
#include <stack>
#include <queue>
#include <string>

class BankingSystem {
private:
    std::unordered_map<int, Account*> accounts;
    std::stack<Transaction> undoStack;
    std::queue<Transaction> requestQueue;
    int nextAccountNumber;

public:
    BankingSystem();
    ~BankingSystem();
    
    // Account management
    bool createAccount(const std::string& holderName, double initialDeposit = 0.0);
    bool deleteAccount(int accountNumber);
    Account* findAccount(int accountNumber) const;
    
    // Transaction operations
    bool deposit(int accountNumber, double amount);
    bool withdraw(int accountNumber, double amount);
    bool transfer(int fromAccount, int toAccount, double amount);
    
    // Special features
    void processPendingRequests();
    bool undoLastTransaction();
    void addToRequestQueue(const Transaction& txn);
    
    // Display functions
    void displayAllAccounts() const;
    void displayAccountDetails(int accountNumber) const;
    
    // Utility
    int getNextAccountNumber() { return nextAccountNumber++; }
    size_t getAccountsCount() const { return accounts.size(); }
};

#endif