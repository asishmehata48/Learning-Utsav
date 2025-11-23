#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Transaction.h"
#include <string>

class Account {
private:
    int accountNumber;
    std::string accountHolder;
    double balance;
    TransactionNode* transactionHistory;

public:
    Account(int accNum, const std::string& holder, double initialBalance = 0.0);
    ~Account();
    
    // Transaction management
    void addTransaction(Transaction::Type type, double amount, const std::string& desc);
    void addTransferTransaction(Transaction::Type type, double amount, int toAccount, const std::string& desc);
    void displayTransactionHistory() const;
    int countTransactions() const;
    
    // Balance operations
    bool deposit(double amount);
    bool withdraw(double amount);
    
    // Getters
    int getAccountNumber() const { return accountNumber; }
    std::string getAccountHolder() const { return accountHolder; }
    double getBalance() const { return balance; }
    TransactionNode* getTransactionHistory() const { return transactionHistory; }
    
    // For undo operations
    bool reverseTransaction(const Transaction& txn);
};

#endif