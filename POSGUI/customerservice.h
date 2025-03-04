#ifndef CUSTOMERSERVICE_H
#define CUSTOMERSERVICE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Customer {
private:
    string phonenumber;
public:
    string name;
    int point;
    Customer(string, string, int);
    string getPnumber() const;
    void addpoint(int);
    void minuspoint(int);
};

inline Customer::Customer(string Pnumber, string n, int p) {
    phonenumber = Pnumber;
    name = n;
    point = p;
}

inline string Customer::getPnumber() const {
    return phonenumber;
}

inline void Customer::addpoint(int x) {
    if (x > 0) {
        point += x;
    }
}

inline void Customer::minuspoint(int x) {
    if (x > 0 && point >= x) {
        point -= x;
    }
}

extern vector<Customer> customerlist;

inline void saveCustomerToFile() {
    ofstream outFile("customer.txt");
    if (outFile.is_open()) {
        for (const auto& customer : customerlist) {
            outFile << customer.getPnumber() << ","
                << customer.name << ","
                << customer.point << "\n";
        }
        outFile.close();
    }
    else {

        cerr << "Error: Could not open customer.txt for writing" << endl;
    }
}

inline void loadCustomerFromFile() {
    customerlist.clear(); 

    ifstream inFile("customer.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string phone, name;
            int point;

            getline(ss, phone, ',');
            getline(ss, name, ',');
            ss >> point;

            customerlist.push_back(Customer(phone, name, point));
        }
        inFile.close();
    }
    else {
     
        ofstream createFile("customer.txt");
        createFile.close();
    }
}

inline void initializeCustomerList() {
    loadCustomerFromFile();
}

inline void addCustomer(string phone, string name, int point) {
    for (const auto& customer : customerlist) {
        if (customer.getPnumber() == phone) {
            return; 
        }
    }

    customerlist.push_back(Customer(phone, name, point));
    saveCustomerToFile();
}

inline string addCustomerPoint(string phone, int x) {
    for (auto& c : customerlist) {
        if (c.getPnumber() == phone) {
            c.addpoint(x);
            saveCustomerToFile();
            return "Point added";
        }
    }
    return "Can't find number";
}

inline bool checkcustomer(string phone) {
    for (auto& c : customerlist) {
        if (c.getPnumber() == phone) {
            return true;
        }
        else
        {
            return false;
        }
    }
}

inline int checkpoint(string phone) {
    for (auto& c : customerlist) {
        if (c.getPnumber() == phone) {
            return c.point;
        }
        else
        {
            return 0;
        }
    }
}

inline string minusCustomerPoint(string phone, int x) {
    for (auto& c : customerlist) {
        if (c.getPnumber() == phone) {
            if (c.point >= x) {
                c.minuspoint(x);
                saveCustomerToFile();
                return "Point have been decreased";
            }
            else {
                return "not enough point";
            }
        }
    }
    return "Can't find number";
}

#endif 