#include "Account.h"
#include <iostream>
#include <iomanip>

Account::Account(int accNum, const std::string& holder, double initialBalance) 
    : accountNumber(accNum), accountHolder(holder), balance(initialBalance), 
      transactionHistory(nullptr) {
    
    if (initialBalance > 0) {
        addTransaction(Transaction::DEPOSIT, initialBalance, "Account Opening");
    }
}

Account::~Account() {
    // Clean up linked list
    TransactionNode* current = transactionHistory;
    while (current != nullptr) {
        TransactionNode* next = current->next;
        delete current;
        current = next;
    }
}

void Account::addTransaction(Transaction::Type type, double amount, const std::string& desc) {
    Transaction newTxn(type, accountNumber, amount, desc);
    TransactionNode* newNode = new TransactionNode(newTxn);
    newNode->next = transactionHistory;
    transactionHistory = newNode;
}

void Account::addTransferTransaction(Transaction::Type type, double amount, int toAccount, const std::string& desc) {
    Transaction newTxn(type, accountNumber, amount, desc);
    newTxn.setToAccount(toAccount);
    TransactionNode* newNode = new TransactionNode(newTxn);
    newNode->next = transactionHistory;
    transactionHistory = newNode;
}

void Account::displayTransactionHistory() const {
    std::cout << "\n--- Transaction History for Account: " << accountNumber << " ---" << std::endl;
    std::cout << "Account Holder: " << accountHolder << std::endl;
    std::cout << "Current Balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    TransactionNode* current = transactionHistory;
    int count = 0;
    
    while (current != nullptr && count < 10) {
        std::cout << "ID: " << current->data.getTransactionId() 
                  << " | Type: " << current->data.getTypeString()
                  << " | Amount: $" << std::fixed << std::setprecision(2) << current->data.getAmount()
                  << " | Time: " << current->data.getTimestamp();
        
        if (current->data.getType() == Transaction::TRANSFER) {
            std::cout << " | To: " << current->data.getToAccount();
        }
        
        if (!current->data.getDescription().empty()) {
            std::cout << " | Desc: " << current->data.getDescription();
        }
        std::cout << std::endl;
        
        current = current->next;
        count++;
    }
    
    if (current != nullptr) {
        std::cout << "... and " << countTransactions() - 10 << " more transactions" << std::endl;
    }
}

int Account::countTransactions() const {
    int count = 0;
    TransactionNode* current = transactionHistory;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

bool Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        addTransaction(Transaction::DEPOSIT, amount, "Cash Deposit");
        return true;
    }
    return false;
}

bool Account::withdraw(double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        addTransaction(Transaction::WITHDRAWAL, amount, "Cash Withdrawal");
        return true;
    }
    return false;
}

bool Account::reverseTransaction(const Transaction& txn) {
    switch(txn.getType()) {
        case Transaction::DEPOSIT:
            return withdraw(txn.getAmount());
        case Transaction::WITHDRAWAL:
            return deposit(txn.getAmount());
        case Transaction::TRANSFER:
            // For transfers, we need external handling
            return deposit(txn.getAmount());
        default:
            return false;
    }
}