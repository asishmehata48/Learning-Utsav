#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

class Transaction {
public:
    enum Type { DEPOSIT, WITHDRAWAL, TRANSFER };
    
    Transaction(Type t, int from, double amt, const std::string& desc = "");
    
    // Getters
    std::string getTransactionId() const { return transactionId; }
    Type getType() const { return type; }
    int getFromAccount() const { return fromAccount; }
    int getToAccount() const { return toAccount; }
    double getAmount() const { return amount; }
    std::string getTimestamp() const { return timestamp; }
    std::string getDescription() const { return description; }
    
    // Setters for transfer transactions
    void setToAccount(int toAcc) { toAccount = toAcc; }
    void setDescription(const std::string& desc) { description = desc; }
    
    std::string getTypeString() const;

private:
    std::string transactionId;
    Type type;
    int fromAccount;
    int toAccount; // For transfers
    double amount;
    std::string timestamp;
    std::string description;
    
    std::string generateTransactionId();
    std::string getCurrentTime();
};

// Transaction Node for Linked List
struct TransactionNode {
    Transaction data;
    TransactionNode* next;
    
    TransactionNode(const Transaction& txn) : data(txn), next(nullptr) {}
};

#endif