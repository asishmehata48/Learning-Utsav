#include "Transaction.h"
#include <sstream>
#include <iomanip>

Transaction::Transaction(Type t, int from, double amt, const std::string& desc) 
    : type(t), fromAccount(from), amount(amt), description(desc), toAccount(-1) {
    transactionId = generateTransactionId();
    timestamp = getCurrentTime();
}

std::string Transaction::generateTransactionId() {
    return "TXN" + std::to_string(rand() % 10000);
}

std::string Transaction::getCurrentTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    std::string timeStr(dt);
    return timeStr.substr(0, timeStr.length()-1); // Remove newline
}

std::string Transaction::getTypeString() const {
    switch(type) {
        case DEPOSIT: return "DEPOSIT";
        case WITHDRAWAL: return "WITHDRAWAL";
        case TRANSFER: return "TRANSFER";
        default: return "UNKNOWN";
    }
}