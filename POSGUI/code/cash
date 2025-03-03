#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// Class representing an item
class Item {
public:
    string name;
    double price;
    int quantity;

    Item(string n, double p, int q) : name(n), price(p), quantity(q) {}
};

// Function to convert currency (Supports USD, THB, JPY)
double convertCurrency(double amount, string from, string to) {
    if (from == "USD" && to == "THB") return amount * 35.0;
    if (from == "USD" && to == "JPY") return amount * 150.0;
    if (from == "THB" && to == "USD") return amount / 35.0;
    if (from == "THB" && to == "JPY") return amount * 4.3;
    if (from == "JPY" && to == "USD") return amount / 150.0;
    if (from == "JPY" && to == "THB") return amount / 4.3;
    return amount;
}

// Base class: Payment
class Payment {
protected:
    double amount;
    string currency;
public:
    Payment(double amt, string curr) : amount(amt), currency(curr) {}
    virtual void processPayment() = 0;
    virtual void printReceipt() {
        cout << "\n----- Payment Receipt -----\n";
        cout << "Total Paid: " << amount << " " << currency << "\n";
        cout << "Thank you for your purchase!\n";
        cout << "--------------------------\n\n";
    }
    virtual ~Payment() {}
};

// Derived class: CreditCardPayment
class CreditCardPayment : public Payment {
private:
    string cardNumber;
    string cardHolder;
    string expiryDate;
    int installments;
public:
    CreditCardPayment(double amt, string curr, string cardNum, string holder, string expiry, int inst = 1)
        : Payment(amt, curr), cardNumber(cardNum), cardHolder(holder), expiryDate(expiry), installments(inst) {}

    void processPayment() override {
        cout << "Processing Credit Card Payment...\n";
        cout << "Card Holder: " << cardHolder << "\n";
        cout << "Card Number: **** **** **** " << cardNumber.substr(cardNumber.length() - 4) << "\n";
        cout << "Expiry Date: " << expiryDate << "\n";
        cout << "Installments: " << installments << " months\n";
        cout << "Amount per installment: " << amount / installments << " " << currency << "\n";
        cout << "Payment Successful!\n";
        printReceipt();
    }
};

// Derived class: PayPalPayment
class PayPalPayment : public Payment {
private:
    string email;
public:
    PayPalPayment(double amt, string curr, string mail) : Payment(amt, curr), email(mail) {}

    void processPayment() override {
        cout << "Processing PayPal Payment...\n";
        cout << "PayPal Email: " << email << "\n";
        cout << "Amount: " << amount << " " << currency << "\n";
        cout << "Payment Successful!\n";
        printReceipt();
    }
};

// Derived class: BankTransferPayment
class BankTransferPayment : public Payment {
private:
    string bankName;
    string accountNumber;
public:
    BankTransferPayment(double amt, string curr, string bank, string accNum) : Payment(amt, curr), bankName(bank), accountNumber(accNum) {}

    void processPayment() override {
        cout << "Processing Bank Transfer Payment...\n";
        cout << "Bank Name: " << bankName << "\n";
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Amount: " << amount << " " << currency << "\n";
        cout << "Payment Successful!\n";
        printReceipt();
    }
};

int main() {
    vector<Item> cart;
    int numItems;
    string currency;
    cout << "Enter currency (USD, THB, JPY): ";
    cin >> currency;

    cout << "Enter number of items: ";
    cin >> numItems;

    for (int i = 0; i < numItems; i++) {
        string name;
        double price;
        int quantity;
        cout << "Enter item name: ";
        cin >> ws;
        getline(cin, name);
        cout << "Enter item price in " << currency << ": ";
        cin >> price;
        cout << "Enter item quantity: ";
        cin >> quantity;
        cart.push_back(Item(name, price, quantity));
    }

    double totalAmount = 0;
    cout << "Shopping Cart:\n";
    for (const auto& item : cart) {
        cout << item.name << " x" << item.quantity << " - " << item.price * item.quantity << " " << currency << "\n";
        totalAmount += item.price * item.quantity;
    }
    cout << "Total Amount: " << totalAmount << " " << currency << "\n";

    // Choose payment method
    int choice;
    cout << "Select Payment Method:\n1. Credit Card\n2. PayPal\n3. Bank Transfer\nChoice: ";
    cin >> choice;
    Payment* payment = nullptr;

    if (choice == 1) {
        string cardNum, holder, expiry;
        int installments;
        cout << "Enter Card Number: ";
        cin >> cardNum;
        cout << "Enter Card Holder Name: ";
        cin.ignore();
        getline(cin, holder);
        cout << "Enter Expiry Date (MM/YY): ";
        cin >> expiry;
        cout << "Enter Installments (1-12 months): ";
        cin >> installments;
        if (installments < 1 || installments > 12) installments = 1;
        payment = new CreditCardPayment(totalAmount, currency, cardNum, holder, expiry, installments);
    } else if (choice == 2) {
        string email;
        cout << "Enter PayPal Email: ";
        cin >> email;
        payment = new PayPalPayment(totalAmount, currency, email);
    } else if (choice == 3) {
        string bankName, accountNumber;
        cout << "Enter Bank Name: ";
        cin.ignore();
        getline(cin, bankName);
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        payment = new BankTransferPayment(totalAmount, currency, bankName, accountNumber);
    } else {
        cout << "Invalid choice! Exiting...\n";
        return 1;
    }

    payment->processPayment();
    delete payment;

    return 0;
}