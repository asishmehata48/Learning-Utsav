#include "BankingSystem.h"
#include <iostream>
#include <limits>

using namespace std;

void displayMenu() {
    cout << "\n=== BANKING SYSTEM ===" << endl;
    cout << "1. Create New Account" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Transfer Funds" << endl;
    cout << "5. View Account Details" << endl;
    cout << "6. View All Accounts" << endl;
    cout << "7. Undo Last Transaction" << endl;
    cout << "8. Process Pending Requests" << endl;
    cout << "9. Delete Account" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose an option: ";
}

int main() {
    BankingSystem bank;
    int choice;
    
    // Add some sample accounts for testing
    bank.createAccount("John Doe", 1000.0);
    bank.createAccount("Jane Smith", 500.0);
    bank.createAccount("Bob Johnson", 1500.0);
    
    do {
        displayMenu();
        cin >> choice;
        
        switch(choice) {
            case 1: {
                string name;
                double deposit;
                cout << "Enter account holder name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter initial deposit: $";
                cin >> deposit;
                bank.createAccount(name, deposit);
                break;
            }
            case 2: {
                int accNum;
                double amount;
                cout << "Enter account number: ";
                cin >> accNum;
                cout << "Enter deposit amount: $";
                cin >> amount;
                if (bank.deposit(accNum, amount)) {
                    cout << "Deposit successful!" << endl;
                } else {
                    cout << "Deposit failed!" << endl;
                }
                break;
            }
            case 3: {
                int accNum;
                double amount;
                cout << "Enter account number: ";
                cin >> accNum;
                cout << "Enter withdrawal amount: $";
                cin >> amount;
                if (bank.withdraw(accNum, amount)) {
                    cout << "Withdrawal successful!" << endl;
                } else {
                    cout << "Withdrawal failed!" << endl;
                }
                break;
            }
            case 4: {
                int fromAcc, toAcc;
                double amount;
                cout << "Enter source account number: ";
                cin >> fromAcc;
                cout << "Enter destination account number: ";
                cin >> toAcc;
                cout << "Enter transfer amount: $";
                cin >> amount;
                if (bank.transfer(fromAcc, toAcc, amount)) {
                    cout << "Transfer successful!" << endl;
                } else {
                    cout << "Transfer failed!" << endl;
                }
                break;
            }
            case 5: {
                int accNum;
                cout << "Enter account number: ";
                cin >> accNum;
                bank.displayAccountDetails(accNum);
                break;
            }
            case 6:
                bank.displayAllAccounts();
                break;
            case 7:
                if (bank.undoLastTransaction()) {
                    cout << "Undo successful!" << endl;
                } else {
                    cout << "Undo failed!" << endl;
                }
                break;
            case 8:
                bank.processPendingRequests();
                break;
            case 9: {
                int accNum;
                cout << "Enter account number to delete: ";
                cin >> accNum;
                bank.deleteAccount(accNum);
                break;
            }
            case 0:
                cout << "Thank you for using our Banking System!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
        
    } while (choice != 0);
    
    return 0;
}