#include <iostream>
#include <vector>
using namespace std;

class Customer {
private:
    string firstName;
    string lastName;
    string phoneNumber;
    int points;

public:
    // Constructor
    Customer(string fName, string lName, string phone)
        : firstName(fName), lastName(lName), phoneNumber(phone), points(0) {}

    // Display customer info
    void displayCustomer() {
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Phone: " << phoneNumber << endl;
        cout << "Points: " << points << endl;
    }

    // Add points
    void addPoints(int p) {
        points += p;
        cout << p << " points added!" << endl;
    }

    // Redeem points
    void redeemPoints(int p) {
        if (p > points) {
            cout << "Not enough points to redeem." << endl;
        } else {
            points -= p;
            cout << p << " points redeemed!" << endl;
        }
    }
};

int main() {
    vector<Customer> customers;

    // Adding customers
    customers.emplace_back("John", "Doe", "123-456-7890");
    customers.emplace_back("Alice", "Smith", "987-654-3210");

    // Displaying customers
    for (auto &c : customers) {
        c.displayCustomer();
        cout << "---------------------" << endl;
    }

    // Adding and redeeming points
    customers[0].addPoints(50);
    customers[0].redeemPoints(20);
    customers[0].displayCustomer();

    return 0;
}
