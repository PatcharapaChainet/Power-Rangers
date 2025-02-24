#include <iostream>
#include <vector>
#include <iomanip>  // For formatting output

using namespace std;

// Class to store transaction details
class Transaction {
private:
    string description;
    double amount;
    bool isIncome; // true = Income, false = Expense

public:
    // Constructor
    Transaction(string desc, double amt, bool income)
        : description(desc), amount(amt), isIncome(income) {}

    // Function to display transaction details
    void display() const {
        cout << left << setw(20) << description
             << setw(10) << (isIncome ? "+" : "-") << fixed << setprecision(2) << amount << endl;
    }

    // Function to get the signed amount
    double getAmount() const {
        return isIncome ? amount : -amount;
    }
};

// Class to manage finance transactions
class FinanceManager {
private:
    vector<Transaction> transactions; // Stores all transactions
    double balance; // Stores the total balance

public:
    // Constructor
    FinanceManager() : balance(0) {}

    // Function to add a new transaction
    void addTransaction(string desc, double amt, bool isIncome) {
        transactions.push_back(Transaction(desc, amt, isIncome));
        balance += (isIncome ? amt : -amt);
    }

    // Function to display all transactions
    void showTransactions() const {
        cout << "\n===== Income & Expense List =====\n";
        cout << left << setw(20) << "Description" << setw(10) << "Amount" << endl;
        cout << "----------------------------------\n";
        for (const auto& t : transactions) {
            t.display();
        }
        cout << "----------------------------------\n";
        cout << "Total Balance: $" << fixed << setprecision(2) << balance << endl;
    }
};

// Main function
int main() {
    FinanceManager manager;
    int choice;

    do {
        cout << "\n==== Income & Expense Tracker ====";
        cout << "\n1. Add Transaction";
        cout << "\n2. Show Transactions";
        cout << "\n3. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string desc;
            double amount;
            int type;
            cout << "Enter description: ";
            cin.ignore(); // Prevents input issues
            getline(cin, desc);
            cout << "Enter amount: ";
            cin >> amount;
            cout << "Type (1=Income, 0=Expense): ";
            cin >> type;

            manager.addTransaction(desc, amount, type == 1);
            cout << "Transaction added successfully!\n";
        } else if (choice == 2) {
            manager.showTransactions();
        }

    } while (choice != 3);

    cout << "Exiting program...\n";
    return 0;
}
