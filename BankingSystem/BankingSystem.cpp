#include "BankingSystem.h"
#include <iostream>
#include <iomanip>

BankingSystem::BankingSystem() : nextAccountNumber(1001) {}

BankingSystem::~BankingSystem() {
    for (auto& pair : accounts) {
        delete pair.second;
    }
}

bool BankingSystem::createAccount(const std::string& holderName, double initialDeposit) {
    if (holderName.empty() || initialDeposit < 0) {
        return false;
    }
    
    int accNum = getNextAccountNumber();
    Account* newAccount = new Account(accNum, holderName, initialDeposit);
    accounts[accNum] = newAccount;
    
    std::cout << "Account created successfully!" << std::endl;
    std::cout << "Account Number: " << accNum << std::endl;
    std::cout << "Account Holder: " << holderName << std::endl;
    std::cout << "Initial Balance: $" << std::fixed << std::setprecision(2) << initialDeposit << std::endl;
    
    return true;
}

bool BankingSystem::deleteAccount(int accountNumber) {
    auto it = accounts.find(accountNumber);
    if (it != accounts.end()) {
        delete it->second;
        accounts.erase(it);
        std::cout << "Account " << accountNumber << " deleted successfully!" << std::endl;
        return true;
    }
    return false;
}

Account* BankingSystem::findAccount(int accountNumber) const {
    auto it = accounts.find(accountNumber);
    return (it != accounts.end()) ? it->second : nullptr;
}

bool BankingSystem::deposit(int accountNumber, double amount) {
    Account* account = findAccount(accountNumber);
    if (account && amount > 0) {
        Transaction txn(Transaction::DEPOSIT, accountNumber, amount, "Bank Deposit");
        undoStack.push(txn);
        return account->deposit(amount);
    }
    return false;
}

bool BankingSystem::withdraw(int accountNumber, double amount) {
    Account* account = findAccount(accountNumber);
    if (account && amount > 0 && account->getBalance() >= amount) {
        Transaction txn(Transaction::WITHDRAWAL, accountNumber, amount, "Cash Withdrawal");
        undoStack.push(txn);
        return account->withdraw(amount);
    }
    return false;
}

bool BankingSystem::transfer(int fromAccount, int toAccount, double amount) {
    Account* fromAcc = findAccount(fromAccount);
    Account* toAcc = findAccount(toAccount);
    
    if (fromAcc && toAcc && fromAcc != toAcc && amount > 0 && fromAcc->getBalance() >= amount) {
        if (fromAcc->withdraw(amount)) {
            toAcc->deposit(amount);
            
            Transaction txn(Transaction::TRANSFER, fromAccount, amount, "Fund Transfer");
            txn.setToAccount(toAccount);
            undoStack.push(txn);
            
            // Add transfer records to both accounts
            fromAcc->addTransferTransaction(Transaction::TRANSFER, amount, toAccount, "Transfer Out");
            toAcc->addTransferTransaction(Transaction::TRANSFER, amount, fromAccount, "Transfer In");
            
            return true;
        }
    }
    return false;
}

void BankingSystem::processPendingRequests() {
    std::cout << "Processing " << requestQueue.size() << " pending requests..." << std::endl;
    
    while (!requestQueue.empty()) {
        Transaction txn = requestQueue.front();
        requestQueue.pop();
        
        // Process the transaction
        // This is simplified - in real system, you'd have proper request processing
        std::cout << "Processed: " << txn.getTypeString() 
                  << " for Account " << txn.getFromAccount() 
                  << " Amount: $" << txn.getAmount() << std::endl;
    }
}

bool BankingSystem::undoLastTransaction() {
    if (undoStack.empty()) {
        std::cout << "No transactions to undo!" << std::endl;
        return false;
    }
    
    Transaction lastTxn = undoStack.top();
    undoStack.pop();
    
    Account* account = findAccount(lastTxn.getFromAccount());
    if (account) {
        std::cout << "Undoing transaction: " << lastTxn.getTypeString() 
                  << " of $" << lastTxn.getAmount() << std::endl;
        return account->reverseTransaction(lastTxn);
    }
    
    return false;
}

void BankingSystem::displayAllAccounts() const {
    std::cout << "\n=== ALL ACCOUNTS ===" << std::endl;
    std::cout << "Total Accounts: " << accounts.size() << std::endl;
    std::cout << "-------------------" << std::endl;
    
    for (const auto& pair : accounts) {
        Account* acc = pair.second;
        std::cout << "Account: " << acc->getAccountNumber()
                  << " | Holder: " << acc->getAccountHolder()
                  << " | Balance: $" << std::fixed << std::setprecision(2) << acc->getBalance()
                  << " | Transactions: " << acc->countTransactions() << std::endl;
    }
}

void BankingSystem::displayAccountDetails(int accountNumber) const {
    Account* account = findAccount(accountNumber);
    if (account) {
        account->displayTransactionHistory();
    } else {
        std::cout << "Account not found!" << std::endl;
    }
}